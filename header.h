#include <iostream>
#include<map>
#include<vector>
#include<iterator>
#include <sstream>
#include <iomanip>

using namespace std;

//Adjacency List class
class AdjacencyList
{
private:
    //Adjacency list map, Key = int url ID, & Values = maps of int url ID that points to key url, and its rank
    map<int, map<int, double>> adjListMap;

public:

    //Getting the from url
    string getP(string P)
    {
        //Creating temp istringstream object, treat as stream
        istringstream temp(P);
        //Create string word
        string word;
        //Extract characters from string word, up until first whitespace
        temp >> word;
        //Return the word
        return word;
    }

    //Getting the to url
    string getN(string N)
    {
        //Creating temp istringstream object, treat as stream
        istringstream temp(N);
        //Create string word
        string word;
        //Create string word2
        string word2;
        //Extract characters from string word, up until first whitespace
        temp >> word >> word2;
        //Return the second word
        return word2;
    }

    //Funtion to take in user data and process it, also returns the number of power iterations
    int insertData(map<string, int>& urlIDMap)
    {
        //Create string for line
        string str;
        //Get line which is the command
        getline(cin, str);

        //Get the number of lines and number of power iterations
        int n = stoi(getP(str));
        int p = stoi(getN(str));

        //For loop to take in urls
        for (int i = 0; i < n; i++)
        {
            //Strings for first and second urls
            string url1;
            string url2;

            //Take in the url values
            cin >> url1 >> url2;

            //Integers for first and second url IDs
            int url1ID;
            int url2ID;

            //Update the map with the url ID if it is unique
            //Checks if url1 is already found in map, and if not then
            if (urlIDMap.find(url1) == urlIDMap.end())
            {
                //Get the value of the first url ID
                url1ID = static_cast<int>(urlIDMap.size());
                //Insert the url and set it to an ID, which should be the current size of the map
                urlIDMap[url1] = static_cast<int>(urlIDMap.size());
            }
            //ELse ID is already in the map
            else
            {
                //Get the value of the first url ID
                url1ID = urlIDMap[url1];
            }
            //Checks if url2 is already found in map, and if not then
            if (urlIDMap.find(url2) == urlIDMap.end())
            {
                //Get the value of the second url ID
                url2ID = static_cast<int>(urlIDMap.size());
                //Insert the url and set it to an ID, which should be the current size of the map
                urlIDMap[url2] = static_cast<int>(urlIDMap.size());
            }
            //ELse ID is already in the map
            else
            {
                //Get the value of the second url ID
                url2ID = urlIDMap[url2];
            }

            //Update the rank of the adjacency list, and insert values
            adjListMap[url2ID][url1ID] = 0.0;
        }

        //If all the IDs are present in adjListMap
        if (adjListMap.size() == urlIDMap.size())
        {
            //Just return number of power iterations
            return p;
        }
        //Else, means there's a url with no incoming, need to add it to adjListMap
        else
        {
            //Iterate through urls in urlIDMap
            for (auto& url : urlIDMap)
            {
                //If there are any urls present in urlIDMap, but not present in adjListMap
                if (adjListMap.find(url.second) == adjListMap.end())
                {
                    adjListMap[url.second] = {};
                }
            }

            //Return the power iterations number
            return p;
        }
    }

    //Function to get the outDegree
    int getOutDegree(int ID)
    {
        //Set count to 0
        int count = 0;

        //For loop to iterate through map
        for (auto& urls : adjListMap)
        {
            for (auto& inUrls : urls.second)
            {
                //If inUrl ID is equal to the ID
                if (inUrls.first == ID)
                {
                    //Increment count
                    count++;
                }
            }
        }

        //Return count
        return count;
    }


    //Prints the pagerank of all the urls, n = number of power iterations
    void pageRank()
    {
        //Create "mechanism to store unique vertices" Int is url ID, and string is url
        map<string, int> urlIDMap;

        //Call the getting user data method, and get num of power iterations:
        int n = insertData(urlIDMap);

        //Get the r value to multiply the matrix
        double r = 1.0 / static_cast<int>(adjListMap.size());

        //Create new map representing r(0) value with each url, aka "second matrix" in project 2 breakdown how are ranks calculated
        map<int, double> rMap;

        //Insert values into the rMap
        for (auto& url : adjListMap)
        {
            //Set int ID to the url ID in adjListMap
            int ID = url.first;
            //Insert the corresponding ID and r value in rMap
            rMap[ID] = r;
        }

        //If the number of power iterations is 1, then just print r(0)
        if (n == 1)
        {
            // Print out list of urls and their page ranks
            for (auto& url : urlIDMap)
            {
                //Get the values to print out
                int ID = url.second;
                string currUrl = url.first;
                double urlRank = rMap[ID];

                //Print out the lines
                cout << currUrl << " " << fixed << setprecision(2) << urlRank << endl;

            }

            //Stop the code from continuing
            return;
        }

        //Need to get value for the "first matrix" as seen in project 2 breakdown how are ranks calculated
        for (auto& url : adjListMap)
        {
            for (auto& inUrl : url.second)
            {
                //Integer for ID of out url
                int currUrl = inUrl.first;

                //Get the outDegree value
                double outDegree = getOutDegree(currUrl);

                //Calculate the pageRank of url
                double pageRank = 1.0 / outDegree;

                //Set pagerank of outUrl equal to pageRank
                inUrl.second = pageRank;
            }
        }

        //Map to represent pageRank for each url after first power iteration r(1)
        map<int, double> pageRanksMap = rMap;

        //Multiply the "matrices" together
        for (auto& url : adjListMap)
        {
            //Id for url, aka url.first
            int ID = url.first;
            //Double to represent total pagerank for each url
            double pageRank = 0.0;

            //Loop through the inUrls of the url
            for (auto& inUrl : url.second)
            {
                //Add to the pagerank
                pageRank += rMap[ID] * inUrl.second;
            }

            //Update the page ranks map
            pageRanksMap[ID] = pageRank;
        }

        //If n = 2, print r(1), aka one power iteration
        if (n == 2)
        {
            // Print out list of urls and their page ranks
            for (auto& url : urlIDMap)
            {
                //Get the values to print out
                int ID = url.second;
                string currUrl = url.first;
                double urlRank = pageRanksMap[ID];

                //Print out the lines
                cout << currUrl << " " << fixed << setprecision(2) << urlRank << endl;
            }

            //Stop the code from continuing
            return;
        }

        //Create map for current page ranks for power iterations
        map<int, double> currPageRanksMap;
        //Create map to get final page ranks
        map<int, double> finalPageRanksMap = pageRanksMap;

        //For loop to complete power iterations
        for (int i = 0; i < n - 2; i++)
        {
            //Iterate over urls pointing toward current url
            for (auto& url : adjListMap)
            {
                //url ID
                int ID = url.first;
                //Double to represent total pageRank for current url
                double pageRank = 0.0;

                for (auto& inUrl : url.second)
                {
                    //Get the value of the page rank for each out url
                    pageRank += finalPageRanksMap[inUrl.first] * inUrl.second;
                }

                //Update the page rank values
                currPageRanksMap[ID] = pageRank;
            }

            //Set the final page ranks equal to the current
            finalPageRanksMap = currPageRanksMap;
        }

        //Print out list of urls and their page ranks
        for (auto& url : urlIDMap)
        {
            //Get the values to print out
            int ID = url.second;
            string currUrl = url.first;
            double urlRank = finalPageRanksMap[ID];

            //Print out the lines
            cout << currUrl << " " << fixed << setprecision(2) << urlRank << endl;
        }
    }

};



