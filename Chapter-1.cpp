#include<bits/stdc++.h>
using namespace std;

int PatternCount(string Text, string Pattern)
{
	int count=0;
	for(int i=0;i<Text.size()-Pattern.size()+1;i++)
	{
		if(Text.substr(i,Pattern.size()).compare(Pattern)==0)
			count++;
	}
	return count;
}

auto FrequencyTable(string Text, int k)
{
	std::map<string, int> freqMap;
	int n=Text.size();
	for(int i=0;i<n-k+1;i++)
	{
		freqMap[Text.substr(i,k)]++;
	}
	return freqMap;
}

std::vector<string> FrequentWords(string Text, int k)
{
	vector<string> freqPatterns;
	std::map<string, int> freqMap;
	freqMap=FrequencyTable(Text,k);
	int maxi=0;
	for(auto&& x:freqMap)
		maxi=max(maxi,x.second);
	for(auto&& x:freqMap)
		if(x.second==maxi)
			freqPatterns.push_back(x.first);
	return freqPatterns;
}

string ReverseComplement(string Pattern)
{
	string temp=Pattern;
	string Pattern_rc;
	for(int i=0;i<Pattern.size();i++)
	{
		if(Pattern[i]=='G')
			temp[i]='C';
		else if(Pattern[i]=='C')
			temp[i]='G';
		else if(Pattern[i]=='A')
			temp[i]='T';
		else
			temp[i]='A';
	}
	Pattern_rc=temp;
	reverse(Pattern_rc.begin(),Pattern_rc.end());
	return Pattern_rc;
}

std::vector<int> PatternMatching(string Pattern, string Genome)
{
	std::vector<int> pos;
	for(int i=0;i<Genome.size()-Pattern.size()+1;i++)
	{
		if(Genome.substr(i,Pattern.size()).compare(Pattern)==0)
			pos.push_back(i);
	}
	return pos;
}

std::vector<string> FindClumps(string Text, int k, int L, int t)
{
	set<string> temp;
	std::vector<string> Patterns;
	int n=Text.size();
	for(int i=0;i<n-L+1;i++)
	{
		string Window=Text.substr(i,L);
		std::map<string, int> freqMap=FrequencyTable(Window,k);
		for(auto&& x:freqMap)
		{
			if(x.second>=t)
				temp.insert(x.first);
		}
	}
	for(auto x:temp)
		Patterns.push_back(x);
	return Patterns;
}

std::vector<int> Skew(string Genome)
{
	std::vector<int> skew(Genome.size()+1);
	skew[0]=0;
	for(int i=0;i<Genome.size();i++)
	{
		int x=0;
		if(Genome[i]=='C')
			x=-1;
		else if(Genome[i]=='G')
			x=1;
		skew[i+1]=skew[i]+x;
	}
	return skew;
}

std::vector<int> MinSkew(string Genome)
{
	std::vector<int> minSkew;
	std::vector<int> skew=Skew(Genome);
	int mini=0;
	for(auto x:skew)
		mini=min(mini,x);
	for(int i=0;i<skew.size();i++)
		if(skew[i]==mini)
			minSkew.push_back(i);
	return minSkew;
}

int HammingDistance(string s1,string s2)
{
	int cnt=0;
	for(int i=0;i<s1.size();i++)
	{
		if(s1[i]!=s2[i])
			cnt++;
	}
	return cnt;
}

std::vector<int> ApproximatePatternMatching(string Pattern, string Text, int d)
{
	std::vector<int> pos;
	for(int i=0;i<Text.size()-Pattern.size()+1;i++)
	{
		if(HammingDistance(Text.substr(i,Pattern.size()),Pattern)<=d)
			pos.push_back(i);
	}
	return pos;
}

int ApproximatePatternCount(string Pattern, string Text, int d)
{
	std::vector<int> pos=ApproximatePatternMatching(Pattern, Text, d);
	return pos.size();
}

set<string> Neighbors(string Pattern, int d)
{
	set<string> Neighborhood;
	if(d==0)
		Neighborhood.insert(Pattern);
	else
	{
		if(Pattern.size()==1)
		{
			Neighborhood.insert("A");
			Neighborhood.insert("G");
			Neighborhood.insert("T");
			Neighborhood.insert("C");
		}
		else
		{
			string Suffix=Pattern.substr(1);
			set<string> SuffixNeighbors=Neighbors(Suffix, d);
			for(auto x:SuffixNeighbors)
			{
				if(HammingDistance(x,Suffix)<d)
				{
					Neighborhood.insert("A"+x);
					Neighborhood.insert("G"+x);
					Neighborhood.insert("C"+x);
					Neighborhood.insert("T"+x);
				}
				else
					Neighborhood.insert(Pattern[0]+x);
			}
		}
	}
	return Neighborhood;
}

std::vector<string> FrequentWordsWithMismatches(string Text, int k, int d)
{
	std::vector<string> Patterns;
	std::map<string, int> freqMap;
	int n=Text.size();
	for(int i=0;i<n-k+1;i++)
	{
		string Pattern=Text.substr(i,k);
		set<string> neighborhood=Neighbors(Pattern, d);
		for(auto x:neighborhood)
		{
			freqMap[x]++;
		}
	}
	int maxi=0;
	for(auto&& x:freqMap)
	{
		maxi=max(maxi,x.second);
	}
	for(auto&& x:freqMap)
	{
		if(x.second==maxi)
			Patterns.push_back(x.first);
	}
	return Patterns;
}

std::vector<string> FrequentWordsWithMismatchesAndReverse(string Text, int k, int d)
{
	std::vector<string> Patterns;
	std::map<string, int> freqMap;
	int n=Text.size();
	for(int i=0;i<n-k+1;i++)
	{
		string Pattern=Text.substr(i,k);
		set<string> neighborhood=Neighbors(Pattern, d);
		for(auto x:neighborhood)
		{
			freqMap[x]++;
		}
	}
	int maxi=0;
	for(auto&& x:freqMap)
	{
		maxi=max(maxi,x.second+freqMap[ReverseComplement(x.first)]);
	}
	for(auto&& x:freqMap)
	{
		if(x.second+freqMap[ReverseComplement(x.first)]==maxi)
			Patterns.push_back(x.first);
	}
	return Patterns;
}

int PatternToNumber(string Pattern)
{
	int temp=1;
	int i=Pattern.size()-1;
	int index=0;
	while(i!=-1)
	{
		int x=0;
		if(Pattern[i]=='C')
			x=1;
		else if(Pattern[i]=='G')
			x=2;
		else if(Pattern[i]=='T')
			x=3;
		index+=temp*x;
		temp*=4;
		i--;
	}
	return index;
}

string NumberToPattern(int index, int k)
{
	string dict[4]={"A","C","G","T"};
	string Pattern="";
	while(index!=0)
	{
		Pattern=dict[index%4]+Pattern;
		index/=4;
	}
	while(Pattern.size()<k)
		Pattern="A"+Pattern;
	return Pattern;
}

std::vector<int> ComputingFrequencies(string Text, int k)
{
	std::vector<int> frequencyArray;
	for(int i=0;i<=Text.size()-k;i++)
	{
		string Pattern=Text.substr(i,k);
		int j=PatternToNumber(Pattern);
		frequencyArray[j]++;
	}
	return frequencyArray;
}

set<string> FasterFrequentWords(string Text, int k)
{
	set<string> FrequentPatterns;
	std::vector<int> frequencyArray=ComputingFrequencies(Text,k);
	int maxi=0;
	for(int i=0;i<pow(4,k);i++)
		maxi=max(maxi,frequencyArray[i]);
	for(int i=0;i<pow(4,k);i++)
	{
		if(frequencyArray[i]==maxi)
		{
			string Pattern=NumberToPattern(i,k);
			FrequentPatterns.insert(Pattern);
		}
	}
	return FrequentPatterns;
}

int main()
{
	//Testers
	
	// string Text="GCGCG";
	// string Pattern="GCG";
	// cout<<PatternCount(Text,Pattern);

	// std::map<string, int> freqMap;
	// string Text="ACGTTGCATGTCGCATGATGCATGAGAGCT";
	// int k=4;
	// freqMap=FrequencyTable(Text,k);
	// for(auto&& x:freqMap)
	// 	cout<<x.first<<" "<<x.second<<endl;

	// string Text="ACGTTGCATGTCGCATGATGCATGAGAGCT";
	// int k=4;
	// vector<string> freqPatterns=FrequentWords(Text,k);
	// for(auto x:freqPatterns)
	// 	cout<<x<<" ";

	// string Pattern="AAAACCCGGT";
	// cout<<ReverseComplement(Pattern);

	// string Pattern="ATAT";
	// string Genome="GATATATGCATATACTT";
	// std::vector<int> pos=PatternMatching(Pattern,Genome);
	// for(auto x:pos)
	// 	cout<<x<<" ";

	// string Text="CGGACTCGACAGATGTGAAGAACGACAATGTGAAGACTCGACACGACAGAGTGAAGAGAAGAGGAAACATTGTAA";
	// int k=5;
	// int L=50;
	// int t=4;
	// std::vector<string> Patterns=FindClumps(Text,k,L,t);
	// for(auto x:Patterns)
	// 	cout<<x<<" ";

	// string Genome="CATGGGCATCGGCCATACGCC";
	// std::vector<int> skew=Skew(Genome);
	// for(auto x:skew)
	// 	cout<<x<<" ";

	// string Genome="TAAAGACTGCCGAGAGGCCAACACGAGTGCTAGAACGAGGGGCGTAAACGCGGGTCCGAT";
	// std::vector<int> minSkew=MinSkew(Genome);
	// for(auto x:minSkew)
	// 	cout<<x<<" ";

	// string s1="GGGCCGTTGGT";
	// string s2="GGACCGTTGAC";
	// cout<<HammingDistance(s1,s2);

	// string Pattern="ATTCTGGA";
	// string Text="CGCCCGAATCCAGAACGCATTCCCATATTTCGGGACCACTGGCCTCCACGGTACGGACGTCAATCAAAT";
	// int d=3;
	// std::vector<int> pos=ApproximatePatternMatching(Pattern, Text, d);
	// for(auto x:pos)
	// 	cout<<x<<" ";

	// string Pattern="AAAAA";
	// string Text="AACAAGCTGATAAACATTTAAAGAG";
	// int d=2;
	// cout<<ApproximatePatternCount(Pattern, Text, d);


	// string Pattern="ACG";
	// int d=1;
	// set<string> Neighborhood=Neighbors(Pattern,d);
	// for(auto x:Neighborhood)
	// 	cout<<x<<endl;

	// string Text="ACGTTGCATGTCGCATGATGCATGAGAGCT";
	// int k=4;
	// int d=1;
	// std::vector<string> Patterns=FrequentWordsWithMismatches(Text,k,d);
	// for(auto x:Patterns)
	// 	cout<<x<<" ";

	// string Text="ACGTTGCATGTCGCATGATGCATGAGAGCT";
	// int k=4;
	// int d=1;
	// std::vector<string> Patterns=FrequentWordsWithMismatchesAndReverse(Text,k,d);
	// for(auto x:Patterns)
	// 	cout<<x<<" ";

	// cout<<NumberToPattern(11,2);
	// cout<<PatternToNumber("GT");

}
