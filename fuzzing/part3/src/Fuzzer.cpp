#include <cstdlib>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstdio>

#include "Mutate.h"
#include "Utils.h"

#include <time.h>

std::string CampaignToStr(Campaign &FuzzCamp) {
  switch (FuzzCamp) {
    case MutationA:
        return "MutationA";
    case MutationB:
        return "MutationB";
    case MutationC:
        return "MutationC";
  }
} 

std::set<int> coverageMap;
int checkCoverage(std::set<int>& map) {
  int cnt = 0;
  char exe[1024];
  int ret = readlink("/proc/self/exe", exe, sizeof(exe) - 1);
  if (ret == -1) {
    fprintf(stderr, "Error: Cannot find /projc/self/exe\n");
    return cnt;
  }
  exe[ret] = 0;

  char logfile[1024];
  int len = strlen(exe);
  strncpy(logfile, exe, len);
  logfile[len] = 0;
  strcat(logfile, ".cov");
  std::ifstream infile(logfile);

  std::string line;
  while (std::getline(infile, line))
  {
    int lineNumber = atoi(line.c_str());
    if (!coverageMap.count(lineNumber)) {
        coverageMap.insert(lineNumber);
        cnt++;
    }
  }

  return cnt;
}


/*
 * Implement your feedback-directed seed update algorithm.
 */
std::pair<std::string,Campaign> selectSeedAndCampaign() {
  int num = rand() % 3 ;
  std::string Seed; 
  Campaign FuzzCamp;

  switch (num) {
    case 0:
    FuzzCamp = MutationB;
    break;

    case 1:
    FuzzCamp = MutationC;
    break;

    case 2:
    FuzzCamp = MutationA;
    break;
  }

  int idx  = rand() % SeedInputs[FuzzCamp].size();
  Seed = SeedInputs[FuzzCamp][idx];

  return std::make_pair(Seed,FuzzCamp);
}

/*
 * Implement your feedback-directed seed update algorithm.
 */
void updateSeedInputs(std::string &Target, std::string &Mutated, Campaign &FuzzCamp, bool Success) {
  bool added = false;

  //case 1: found crash, so a good candiditate to put into the pool
  if (!Success) { // crashes found
     added = true;
  }
  else if (SeedInputs[FuzzCamp].size() < 5000) {
     added = true;
  }
  //case 2: 
  //read coverage file line by line, and check if any new line detected(need to matain a coverage map), then marked it.
  else if (checkCoverage(coverageMap) > 0){ //has covered a new line.
     added = true; 
  }
 
  if (added) {
    SeedInputs[FuzzCamp].push_back(Mutated);
  }
}

int Freq = 1000;
int Count = 0;

bool test(std::string &Target, std::string &Input, Campaign &FuzzCamp, std::string &OutDir) {
  // Clean up old coverage file before running 
  std::string CoveragePath = Target + ".cov";
  std::remove(CoveragePath.c_str());
  Count++;

  int ReturnCode = runTarget(Target, Input);
  switch (ReturnCode) {
  case 0:
    if (Count % Freq == 0)
      storePassingInput(Input, CampaignToStr(FuzzCamp), OutDir);
    return true;
  case 256:
    fprintf(stderr, "%d crashes found\n", failureCount);
    storeCrashingInput(Input, CampaignToStr(FuzzCamp), OutDir);
    return false;
  case 127:
    fprintf(stderr, "%s not found\n", Target.c_str());
    exit(1);
  }
}

// ./fuzzer [exe file] [seed input dir] [output dir]
int main(int argc, char **argv) { 
  if (argc < 4) { 
    printf("usage %s [exe file] [seed input dir] [output dir]\n", argv[0]);
    return 1;
  }

  srand(time(NULL));

  struct stat Buffer;
  if (stat(argv[1], &Buffer)) {
    fprintf(stderr, "%s not found\n", argv[1]);
    return 1;
  }

  if (stat(argv[2], &Buffer)) {
    fprintf(stderr, "%s not found\n", argv[2]);
    return 1;
  }

  if (stat(argv[3], &Buffer)) {
    fprintf(stderr, "%s not found\n", argv[3]);
    return 1;
  }

  if (argc >= 5) {
    Freq = strtol(argv[5], NULL, 10);
  }

  std::string Target(argv[1]);
  std::string SeedInputDir(argv[2]);
  std::string OutDir(argv[3]);

  initialize(OutDir);

  if (readSeedInputs(SeedInputDir)) {
    fprintf(stderr, "Cannot read seed input directory\n");
    return 1;
  }

  while (true) {
      // NOTE: You should feel free to manipulate this run loop 
      std::pair<std::string,Campaign> SC = selectSeedAndCampaign();
      auto Mutant = mutate(SC.first, SC.second);
      auto Success = test(Target, Mutant, SC.second, OutDir);
      updateSeedInputs(Target, Mutant, SC.second, Success);
  }

  return 0;
}
