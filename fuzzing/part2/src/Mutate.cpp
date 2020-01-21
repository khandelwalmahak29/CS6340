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

//const std::string characters = "!@#$^&*ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz";
const std::string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
std::random_device random_device;
std::mt19937 generator(random_device());
std::uniform_int_distribution<> distribution(0, characters.size() - 1);

static inline char randomString() {
  return rand() % 128;
}

static inline char randomChar(){
  return characters[distribution(generator)];
}

std::string mutation1(std::string& Origin, bool ignore) {
    std::string random_string;
    for (std::size_t i = 0; i < Origin.length(); ++i)
    {
	if (ignore && (isspace(Origin[i]) || Origin[i] == ',' || Origin[i] == '.'))  continue;

         Origin[i] = randomString();
    }
    return Origin;
}

std::string mutation2(std::string& s) {
    if (s.length() == 0) return s;
    int d = rand() % s.length();
    reverse(s.begin(), s.begin()+d); 
    reverse(s.begin()+d, s.end()); 
    reverse(s.begin(), s.end()); 
    return s;
}

/*
std::string mutation3(std::string s) {
    if (s.length() == 0) return s;
    int s1 = rand() % s.length();
    int s2 = rand() % s.length();
    std::swap(s[s1],s[s2]); 
    return s;
}

std::string mutation4(std::string s) {
    if (s.length() == 0) return s;
    int s1 = rand() % s.length();
    int sLength = rand() % (s.length() - s1);
    s.erase(s1,sLength + 1);
    return s;
}
*/
std::string mutation5(std::string& s) {
    int s1 = rand() % 10;
    std::string inString;
    for(int i = 0; i <= s1; i++) {
        inString += randomString();
    }
    s +=inString;
    return s;
}

std::string mutation7(std::string& s) {
    std::random_shuffle (s.begin(), s.end());
    return s;
}

enum mutate_type {
    m1,
    m2,
   // m3,
 //   m4,
    m5,
    //m6,
    last
};

std::string mutateA(std::string& Origin) {
   srand (time(NULL)); 
   mutate_type selected = static_cast<mutate_type>(rand() % (last - 1));
   switch (selected) {
   case m1:
      return mutation1(Origin, true);
   case m2:
      return mutation2(Origin);
   }
   return Origin;
}

std::string mutateB(std::string Origin) {
  srand (time(NULL)); 
//switch mutation cases
   mutate_type selected = static_cast<mutate_type>(rand() % last);
   switch (selected) {
   case m1:
      return mutation1(Origin, false);
   case m2:
      return mutation2(Origin);
   case m5:
      return mutation5(Origin);
   }

  return Origin;
}

std::string mutateC(std::string Origin) {
 //for 10 times
  srand (time(NULL)); 
  return mutation7(Origin);
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
