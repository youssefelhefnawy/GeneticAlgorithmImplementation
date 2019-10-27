#include <iostream>
#include<bits/stdc++.h>
using namespace std;
class Item
{
public:
    int Weight;
    int Value;
};
class SolutionInfo
{
public:
    int FitnessValue;
    int Weight;
    vector<int>Solution;
    vector<Item> Items;
    SolutionInfo(int f,int w,vector<int> s)
    {
        FitnessValue=f;
        Weight=w;
        Solution=s;
    }

    SolutionInfo(vector<Item>i)
    {
        Items=i;
    }
    SolutionInfo()
    {
        ;
    }
    void CalculateFitnessFunctionAndCost()
    {
        FitnessValue=0;
        Weight=0;

           for(int i=0;i<Solution.size();i++)
        {

                FitnessValue+=Solution[i]*Items[i].Value;
                Weight+=Solution[i]*Items[i].Weight;

        }
    }

};

vector<int> GenerateBinaryPresentation(int NumOfGenes)
{
    vector<int>arr;
    for(int i=0;i<NumOfGenes;i++)
    {
       arr.push_back(rand()%2);

    }

return arr;
}
 vector<vector<int> >GeneratePopulation(int PopulationSize,int NumOfGenes)
{

vector<vector<int> >Population;
for(int i=0;i<PopulationSize;i++)
{
///Generate Random Binary Solution Here
Population.push_back(GenerateBinaryPresentation(NumOfGenes));//Push Back SOlution
}
return Population;


}



SolutionInfo CaclulateFitnessFuntion_AND_Weight(vector<int> Solution,vector<Item>Items,int SizeOfKnapsack,string option)
{
    //It Returns pair because the first item in the pairs is the fitness function result  and the second is the breeding indicator

    int SolutionCost=0,Fitness=0;
   for(int i=0;i<Solution.size();i++)
   {

       Fitness+=Solution[i]*Items[i].Value;
       SolutionCost+=Solution[i]*Items[i].Weight;

   }
   if(option=="Discard")
   {
       if(SolutionCost>SizeOfKnapsack)
       {

           return SolutionInfo(Fitness,0,Solution); //Important Function
       }
       else
       {

           return SolutionInfo(Fitness,1,Solution); //Important Function
       }
   }
   else if (option=="Difference Between SolutionCost And SizeOfKnapsack") ///
   {
    return SolutionInfo(Fitness,SolutionCost-SizeOfKnapsack,Solution);//Try to minimize the second
   }

}

void PrintPopulation(vector<SolutionInfo> Population,string option,vector<Item>Items )
{

if(option=="Fitness")
{



    for(unsigned j=0;j<Population.size();j++)
    {
        int Fitness=Population[j].FitnessValue;
    }



}
else if(option =="Solution")
{
    for(unsigned j=0;j<Population.size();j++)
    {

    for(unsigned i=0;i<Population[j].Solution.size();i++)
    {

        cout<<Population[j].Solution[i]<<" ";

    }
    cout<<"Printed a Solution"<<endl;
    }

}

}
bool FitnessComparator(SolutionInfo S1,SolutionInfo S2)
{
    return S1.FitnessValue>S2.FitnessValue;
}
void  SortPopulationBasedOnFitness( vector<SolutionInfo> &Population)
{


        sort(Population.begin(),Population.end(),FitnessComparator);

}

vector<SolutionInfo> ApplySelectionBasedOnFitnessFunction(vector<SolutionInfo>Population,float MatingPoolPercent,vector<Item>I)
{
//LastWorking

    vector<SolutionInfo>Parents;

        //Sort Descending
               sort(Population.begin(),Population.end(),FitnessComparator);


                   for(int i=0;i<Population.size()*MatingPoolPercent;i++)
                   {
                       Parents.push_back(Population[i]);
                   }




    return Parents;


}

 SolutionInfo GetOffSpring(SolutionInfo Parent1,SolutionInfo Parent2,int PointOfCrossover,vector<Item>Items)
 {

        vector<int>binarytemp;

     for(int i=0;i<PointOfCrossover;i++)
     {
        // cout<<Parent1.Solution[i]<<"  ";
         binarytemp.push_back(Parent1.Solution[i]);


     }
     for(int i=PointOfCrossover;i<Parent2.Solution.size();i++)
     {
          //cout<<Parent2.Solution[i]<<"  ";
          binarytemp.push_back(Parent2.Solution[i]);
     }
          SolutionInfo Child(Items);
            Child.Solution=binarytemp;
            Child.CalculateFitnessFunctionAndCost();




     return Child;
 }
 vector<SolutionInfo> CrossBreed(vector<SolutionInfo>Parents ,string Option,vector<Item>Items)
 {
     vector<SolutionInfo> OffSprings;

    if(Option=="Single Point")
     {

         ///Random Generation of point of cross breeding

         int PointOfCrossover=rand()%(Parents[0].Solution.size()-1); ///Gets a point index given a certain number of genes





          for(int i=0;i<Parents.size();i++)
          {

            if(i+1 !=Parents.size())
            {
                OffSprings.push_back(GetOffSpring(Parents[i],Parents[i+1],PointOfCrossover,Items));
                OffSprings.push_back(GetOffSpring(Parents[i+1],Parents[i],PointOfCrossover,Items));

            }

          }

     }
     return OffSprings;

 }
vector<SolutionInfo> ApplyMutation(vector<SolutionInfo> Population,float MutationPercentage)
{

    int IndividualSolutionSize=Population[0].Solution.size();


    for(int i=0;i<Population.size();i++)
    {
        float percent;
        for(int j=0;j<IndividualSolutionSize;j++)
        {

                percent= (rand()%100);//Important
            if(percent<=MutationPercentage)
            {
                Population[i].Solution[j]=(1- pow(Population[i].Solution[j],1));
            }
        }
    }
    return Population;
}
vector<SolutionInfo> AddOffSpringsToPopulation(vector<SolutionInfo> Population,vector<SolutionInfo>OffSprings)
{
    for(int i=0;i<OffSprings.size();i++)
    {
        Population.push_back(OffSprings[i]);
    }
    return Population;
}
vector<SolutionInfo> ReplacePopulation(vector<SolutionInfo>  Population,vector<SolutionInfo>  OffSprings,int NoOfParentsToBeKept,int KnapsackSize)//Elite
{
   vector<SolutionInfo> NextGeneration;
    SortPopulationBasedOnFitness(Population);
    for(int i=0;i<Population.size()&&i<NoOfParentsToBeKept;i++)
    {
        NextGeneration.push_back(Population[i]);

    }
    for(int i=0;i<OffSprings.size();i++)
    {
        if(OffSprings[i].Weight<=KnapsackSize)
        {
            NextGeneration.push_back(OffSprings[i]);
        }
    }
    return NextGeneration;

}
void ApplyGA(int PopulationSize,int NumOfGenes,int MaxNoofGenerations,vector<Item>Items,int SizeOfKnapsack)
{
 ///1)
      ///Generate Population


        vector<vector<int> > Population=GeneratePopulation(PopulationSize,NumOfGenes);

    vector<SolutionInfo> CurrentPopulation;
    for(int i=0;i<Population.size();i++) ///Evaluate The Solution through the fitness funciton : EX() 4 * 1 + 6 * 0 + 3 * 1= 7.

        {
            SolutionInfo FitnessAndBreedingIndicator=CaclulateFitnessFuntion_AND_Weight(Population[i],Items,SizeOfKnapsack,"Discard");


            if(FitnessAndBreedingIndicator.Weight!=0)
            CurrentPopulation.push_back(FitnessAndBreedingIndicator);

        }
    // 2) Generations
        for(int i=0;i<MaxNoofGenerations;i++)
        {
              //  cout<<"GENERATION"<<i<<endl;


                ///Choose The Parents to Breed
                        //Let's Say we Choose percentage of parents
                        CurrentPopulation = ApplySelectionBasedOnFitnessFunction(CurrentPopulation,0.5,Items);

                ///Apply CrossOver
                         //   PrintPopulation(CurrentPopulation,"Fitness",Items);

                   vector<SolutionInfo> OffSprings = CrossBreed(CurrentPopulation,"Single Point",Items); ///Those Are the Children after CrossBreeding

                ///Apply Mutation

                     OffSprings=ApplyMutation(OffSprings,1);//2 is the percentage of mutation 100

                ///Replacement Methodology
                    //Steady State //Only Unique Individuals ??!
                       CurrentPopulation= ReplacePopulation(CurrentPopulation,OffSprings,20,SizeOfKnapsack);


        }

        cout<<CurrentPopulation[0] .FitnessValue<<endl;
        int NoOfTakenItems=0;
        for(int i=0;i<NumOfGenes;i++)
        {
            if(CurrentPopulation[0].Solution[i]==1)
            {
                NoOfTakenItems++;
                cout<<"Weight : " <<Items[i].Weight<<" ,"<<"Value : "<<Items[i].Value<<endl;
            }
        }
        cout<<"Number Of Taken Items : "<<NoOfTakenItems<<endl;



}
int main()
{
  ifstream inputfile;
    int C ;//Number of test cases;
    int  NoOfItems ;//Number of items (Maximum 50 item).
    int SizeOfKnapSack ;// Size of knapsack.
    int Pairs ;//pair values representing the weight and benefit of each knapsack (weight, benefit).
    int NoOfGenerations;

    cout<<"Enter No OF Generations"<<endl;
   // cin>>NoOfGenerations;

    inputfile.open("C:\\Users\\Youssef\\Desktop\\Year 4\\Genetic Algorithms\\Assignments\\Assignment 1\\input_example.txt",ios::in);
    inputfile>>C;



    for(int i=0;i<C;i++)
    {

    inputfile>>NoOfItems;
    inputfile>>SizeOfKnapSack;

    //Read Pairs
    vector<Item >Items;
    Item temp;
    //Input the Items Values
    for(int j=0;j<NoOfItems;j++)
    {

        inputfile>>temp.Weight>>temp.Value;
        Items.push_back(temp);

    }


     //Apply Genetic Algorithm Here
     //Dynamic Population Size
     ///pow(2,NoOfItems/2)
     cout<<"Case :"<<i+1<<"  ";
    ///100,9
     NoOfGenerations=NoOfItems;
         ApplyGA(NoOfItems,NoOfItems, NoOfGenerations,Items,SizeOfKnapSack);


    }
    inputfile.close();
    return 0;
}
