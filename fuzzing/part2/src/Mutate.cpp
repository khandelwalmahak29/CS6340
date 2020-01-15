#include "Mutate.h"

#include <cstring>
#include <map>
#include <iostream>
#include <string>
#include <random>
#include<bits/stdc++.h> 

std::map<std::string, Campaign> to_campaign = 
  {{"MutationA", MutationA}, {"MutationB", MutationB}, {"MutationC", MutationC}};

bool toCampaign(std::string Str, Campaign& FuzzCampaign) {
  auto I = to_campaign.find(Str);
  if (I == to_campaign.end()) {
    fprintf(stderr, "\"%s\" not a valid fuzz campaign, choice options are: ", Str.c_str());
    for (auto &I2 : to_campaign) {
      fprintf(stderr, "%s ", I2.first.c_str());
    }
    fprintf(stderr, "\n");
    return false;
  }
  FuzzCampaign = I->second;
  return true;
}

/*
 * Implement your mutation algorithms.
 */

const std::string characters = "!@#$^&*ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz";
std::random_device random_device;
std::mt19937 generator(random_device());
// std::uniform_int_distribution<> distribution(0, characters.size() - 1);

char randomString() {
  // return characters[distribution(generator)];
  return rand() % 128;
}
std::string mutation1(std::string Origin) {
    

    std::string random_string;

    for (std::size_t i = 0; i < Origin.length(); ++i)
    {
        Origin[i] = randomString();
    }

    return Origin;
}

std::string mutation2(std::string s) {
    int d = rand() % s.length();
    reverse(s.begin(), s.begin()+d); 
    reverse(s.begin()+d, s.end()); 
    reverse(s.begin(), s.end()); 

    //std::cout <<"mutation2 called: " << d << " : " << s.length() << std::endl;
    return s;
}
std::string mutation3(std::string s) {
    int s1 = rand() % s.length();
    int s2 = rand() % s.length();
    std::swap(s[s1],s[s2]); 
    return s;
}

std::string mutation4(std::string s) {
    int s1 = rand() % s.length();
    int sLength = rand() % (s.length() - s1);
    s.erase(s1,sLength);
    return s;
}
std::string mutation5(std::string s) {
    int s1 = rand() % 1000;
    std::string inString;
    for(int i = 0; i < s1; i++) {
        inString += randomString();
    }
    s.insert(s.length()-1,inString);
    return s;
}
std::string mutateA(std::string Origin) {
  //switch mutation cases
  srand (time(NULL));
  std::uniform_int_distribution<> distr(1, 100);
  int selectedNum = distr(generator);
  if(selectedNum > 0 && selectedNum < 20) {
      Origin = mutation1(Origin);
  }
  else if(selectedNum > 19 && selectedNum < 40) {
      Origin = mutation2(Origin);
  }
  else if(selectedNum > 39 && selectedNum < 60) {
      Origin = mutation3(Origin);
  }
  else if(selectedNum > 59 && selectedNum < 80) {
     Origin = mutation4(Origin);
  }
  else if(selectedNum > 79 && selectedNum < 101) {
     Origin = mutation5(Origin);
  }
  //std::cout <<"selected Num: "<< selectedNum << std::endl;
  return Origin;
}

std::string mutateB(std::string Origin) {
  //do every mutations
  srand (time(NULL));
  Origin = mutation1(Origin);
  //std::cout <<"mutation1 output: "<< Origin << std::endl;

  Origin = mutation2(Origin);
  //std::cout <<"mutation2 output: "<< Origin << std::endl;

  Origin = mutation3(Origin);
  //std::cout <<"mutation3 output: "<< Origin << std::endl;

  Origin = mutation4(Origin);
  //std::cout <<"mutation4 output: "<< Origin << std::endl;

  Origin = mutation5(Origin);
  return Origin;
}

std::string mutateC(std::string Origin) {
  //for 10 times
  for(int i = 0 ; i < 10; i++){
      Origin = mutateA(Origin);
  }
  return Origin;
}

std::string mutate(std::string Origin, Campaign& FuzzCampaign) {
  std::string Mutant;
  switch (FuzzCampaign) {
    case MutationA:
        return mutateA(Origin);
    case MutationB:
        return mutateB(Origin);
    case MutationC:
        return mutateC(Origin);
  }
}
