/*

            Object Oriented Programming & Advanced Data Structures
   
    Project : Social Media Analysis using Graphs in C++
   
    This project allows users to find the number of mutual
    followers between two accounts, recommend friends, find the
    number of followers, find how distant two accounts are, and see
    how well the user is connected to other users on the platform.
    
    Team members:
    
        1. Aswin Ramanathan V
        2. Kishore Prashanth P
        3. Nikhil Sai V
        
*/

#include<bits/stdc++.h>
using namespace std;

//GLOBAL DECLARATION
int unique_id=0;

//Fn to find the mutual followers between two users
void mutual_followers(string user_1,string user_2,map<string,int>& db,map<int,string>& temp_db,vector<int> adj[]){
    if(db.find(user_1)!=db.end() && db.find(user_2)!=db.end()){
        cout<<"Mutual Followers of "<<user_1<<" with respect to "<<user_2<<" : \n";
        for(auto i : adj[db[user_1]]){
            for(auto j : adj[db[user_2]]){
                if(i==j){
                    cout<<temp_db[i]<<endl;
                }
            }
        }
    }
    else{
        cout<<"The user name doesn't exist\n";
    }
}

//Fn to find the number of mutual followers between two users
void no_of_mutual_followers(string user_1,string user_2,map<string,int>& db,map<int,string>& temp_db,vector<int> adj[]){
    if(db.find(user_1)!=db.end() && db.find(user_2)!=db.end()){
        int cnt=0;
        cout<<"Number of Mutual Followers of "<<user_1<<" with respect to "<<user_2<<" : \n";
        for(auto i : adj[db[user_1]]){
            for(auto j : adj[db[user_2]]){
                if(i==j){
                    cnt++;
                }
            }
        }
        cout<<cnt<<endl;
    }
    else{
        cout<<"\nThe user name doesn't exist";
    }
}

//Fn to find the number of friends of an user
void no_of_friends(string user_1,map<string,int>& db,vector<int> adj[]){
    if(db.find(user_1)!=db.end()){
        cout<<"The number of friends "<<user_1<<" got is "<<adj[db[user_1]].size()<<endl;
    }
    else{
        cout<<"\nThe user name doesn't exists";
    }
    
}

//Fn to display the friends list of an user
void display_friends_list(string user_1,map<string,int>& db,map<int,string>& temp_db,vector<int> adj[]){
    if(db.find(user_1)!=db.end()){
        cout<<"\n Friends List of "<<user_1<<" : \n";
        for(auto it : adj[db[user_1]]){
            cout<<temp_db[it]<<endl;
        }
    }
    else{
        cout<<"\nThe user name doesn't exists";
    }
}

//Fn to recommend friends from the graph
void recommend(string user_1,map<string,int>& db,map<int,string>& temp_db,vector<int> adj[]){
    if(db.find(user_1)!=db.end()){
        cout<<"\nRecommended Friends : \n"<<endl;
        unordered_set<int> check_set;
        for(auto i : adj[db[user_1]]){
            check_set.insert(i);
        }
        for(auto i : adj[db[user_1]]){
            for(auto j : adj[i]){
                if(j!=db[user_1] && check_set.find(j)==check_set.end()){
                    cout<<temp_db[j]<<endl;
                    check_set.insert(j);
                }
            }
        }
    }
    else{
       cout<<"\nThe user name doesn't exists"; 
    }
    
}

//Fn to open the file and check whether it has opened correctly or not
void openFile(ifstream& inFile,string fname){
    //open() to open a file
    inFile.open(fname);
    if(inFile.is_open()){
        //cout<<"\nSuccessfully opened file"<<endl;
    }
    else{
        cout<<"\nFailed to open file"<<endl;
        exit(-1);
    }
}

//Fn implementing dijksta's algorithm to check connection strength between all the users
void dijkstra(int n, map<string,int>& db, vector<pair<int,int> > g[],map<int,string>& temp_db){

    //n denotes the no of users
    //map<string,int> & db denotes the map which holds the name:ID values

    cout<<"\nEnter user name to find its connection strength : ";
    string u;
    cin>>u;
    if(db.find(u)!=db.end()){
        int source=db[u];
        //cout<<"Source is   "<<source<<endl;
        // cin >> source;
        
        // Dijkstra's algorithm begins from here
        priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > pq;
        // min-heap ; In pair => (dist,from)
        // vector<int> distTo(n+1,INT_MAX);     
        // 1-indexed array for calculating shortest paths; 
        vector<int> distTo(n,999); 
        distTo[source] = 0;
        pq.push(make_pair(0,source));   // (dist,from)
        
        while( !pq.empty() ){
            int dist = pq.top().first;
            int prev = pq.top().second;
            pq.pop();
            
            vector<pair<int,int> >::iterator it;
            for( it = g[prev].begin() ; it != g[prev].end() ; it++){
                int next = it->first;
                int nextDist = it->second;
                if( distTo[next] > distTo[prev] + nextDist){
                    distTo[next] = distTo[prev] + nextDist;
                    pq.push(make_pair(distTo[next], next));
                }
            }
            
        }
        
        cout << "The Connection Strength of user, " << u << " are : \n";
        for(int i = 0 ; i<n ; i++){
            if(i!=source){
                cout<<temp_db[i]<<" => "<<distTo[i]<<"%"<<endl;
            }
            cout << "\n";
        }
    }
}

//Fn to find an user with maximim number of friends
void max_friends(vector<int> adj[],map<int,string>& temp_db){
    int maxi=INT_MIN;
    int ans;
    for(auto it=temp_db.begin();it!=temp_db.end();it++){
        //cout<<adj[it->first].size()<<endl;;
        if((int)(adj[it->first].size()) > maxi){
            maxi=adj[it->first].size();
            //cout<<maxi<<endl;
            ans=it->first;
            //cout<<ans<<endl;
            //cout<<ans<<endl;
        }
    }
    
    //Output the name of one user with maximum number of friends
    cout<<"User with maximum number of friends : "<<temp_db[ans]<<endl;
}

//Fn to find an user with minimum number of friends
void min_friends(vector<int> adj[],map<int,string>& temp_db){
    int mini=INT_MAX;
    int ans;
    for(auto it=temp_db.begin();it!=temp_db.end();it++){
        //cout<<adj[it->first].size()<<endl;;
        if((int)(adj[it->first].size()) < mini){
            mini=adj[it->first].size();
            //cout<<maxi<<endl;
            ans=it->first;
            //cout<<ans<<endl;
            //cout<<ans<<endl;
        }
    }
    
    //Output the name of one user with minimum number of friends
    cout<<"User with minimum number of friends : "<<temp_db[ans]<<endl;
}

int main(){
    
    //map to store the user's name
    map<string,int> db;
    
    //map to store the user's name and for accessing
    map<int,string> temp_db;
    
    //Adjacency list to represent the graph
    vector<int> adj[20];
    
    vector<pair<int,int> > g[21]; 
    // for dijkstra
    
    cout<<"\n1 . User Input";
    cout<<"\n2 . Input from File\n";
    cout<<"\nEnter your choice : ";
    int start_choice;
    
    cin>>start_choice;
    
    //Get Graph Input from File(network.txt,friends.txt)
    if(start_choice==2){
        
        //network.txt
        //1.open the file 
        //network.txt => contains all the names of the users
        
        ifstream inFile;
        openFile(inFile,"network.txt");
        
        //2.process the file
        //read line by line from the file network.txt
        string user_name;
        while(!inFile.eof()){
            getline(inFile,user_name);
            
            //adding the user names in the map
            if(db.find(user_name)==db.end()){
                db[user_name]=unique_id;
                temp_db[unique_id]=user_name;
                unique_id++;
            }
            else{
                
                cout<<"\nThe user name already exists";
            }  
            
        }
        
        //3. close the file network.txt
        inFile.close();
        
        //For Debugging
        //vector<int> adj[db.size()];
        //For Debugging
        
        //friends.txt
        //1.open the file friends.txt
        //friends.txt => contains the friends name of the users in network.txt
        
        inFile;
        openFile(inFile,"friends.txt");
        
        //2.process the file
        //read line by line from the file
        string temp_user_name;
        string following_name;
        istringstream iss;
        for(auto it=db.begin();it!=db.end();it++){
            while(!inFile.eof()){
                
            //read word by word from ech ine
                
            getline(inFile,temp_user_name);
                if(inFile.good()){
                    iss.clear();
                    iss.str(temp_user_name);
                    while(iss.good()){
                        iss >> following_name;
                        
                        //adding in the adjacency list to create a graph
                        
                        if(following_name!=it->first && db.find(following_name)!=db.end()){
                            adj[db[it->first]].push_back(db[following_name]);
                            //adj[db[following_name]].push_back(db[it->first]);
                            
                            //for dijkstra
                            g[db[it->first]].push_back(make_pair(db[following_name],1));
                        }
                        else{
                            cout<<"\nThe name doesn't exist";
                        }
                    }
                    break;
                }
            }
        }
        
        //3.close the file friends.txt
        inFile.close();
            
    }
    
    //Menu driven to get user details from output terminal
    else if(start_choice==1){
        
        //Input to get number of users
        int no_of_users;
        
        //Input to get user names
        string user_name;
        
        cout<<"Enter the number of users : ";
        cin>>no_of_users;
        
        //Input user names 
        for(int i=0;i<no_of_users;){
            cout<<"\nEnter User "<<i+1<<" name : ";
            cin>>user_name;
            
            //adding in the map
            
            if(db.find(user_name)==db.end()){
                db[user_name]=i;
                temp_db[i]=user_name;
                i++;
            }
            else{
                cout<<"\nThe user name already exists";
            }      
        }
        
        //For Debugging
        //vector<int> adj[db.size()];
        //For Debugging
        
        //Input friends name from the user
        cout<<"\n Enter Following List ( -1 to complete ) : ";
        for(auto it=db.begin();it!=db.end();it++){
            cout<<"\n"<<it->first<<" : \n";
            
            //Input friends name for each user
            string following_name;
            
            while(1){
                cin>>following_name;
                
                if(following_name=="-1") break;
                
                //adding in the adjacency list to create the graph
                
                else if(following_name!=it->first && db.find(following_name)!=db.end()){
                    adj[db[it->first]].push_back(db[following_name]);
                    //adj[db[following_name]].push_back(db[it->first]);
                    
                    //for dijkstra
                    g[db[it->first]].push_back(make_pair(db[following_name],1));
                }
                else{
                    cout<<"\nThe name doesn't exist";
                }
            }
        } 
    }
    else{
        
        cout<<"\n Invalid Input";
        exit(-1);
        
    }
    
    //For Debugging
    
    //Check db map here
    //for(auto it : db){
    //    cout<<it.first<<" "<<it.second<<endl;
    //}
    
    //Check Graph(Adjaceny list here)
    //for(auto it=db.begin();it!=db.end();it++){
    //    cout<<"\n"<<it->first<<" : ";
    //    for(auto it : adj[it->second]){
    //        cout<<temp_db[it]<<" ";
    //    }
    //    cout<<endl;
    //}
    
    //For Debugging
    
    while(1){
        
        //To get option number from the user
        int option;
        
        //Menu driven options
        cout<<"\n1 . Check Mutual Followers";
        cout<<"\n2 . Number of Mutual Followers";
        cout<<"\n3 . Number of Friends List";
        cout<<"\n4 . Display Friends List";
        cout<<"\n5 . Recommend new Friends";
        cout<<"\n6 . Check Connections Strength";
        cout<<"\n7 . Users with maximum number of Friends";
        cout<<"\n8 . Users with minimum number of Friends";
        
        cout<<"\nEnter your choice : ";
        cin>>option;
        
        //sample variables to get user names 
        string user_1,user_2;
        
        switch(option){
            
            //Check Mutual Followers
            case 1:
                cout<<"\nEnter the user name : ";
                cin>>user_1;
                cout<<"\nEnter the name of the user to check mutual Followers : ";
                cin>>user_2;
                mutual_followers(user_1,user_2,db,temp_db,adj);
                break;
                
            //Number of Mutual Followers    
            case 2:
                cout<<"\nEnter the user name : ";
                cin>>user_1;
                cout<<"\nEnter the name of the user to check mutual Followers : ";
                cin>>user_2;
                no_of_mutual_followers(user_1,user_2,db,temp_db,adj);
                break;
                
            //Number of Friends List
            case 3:
                cout<<"\nEnter the user name : ";
                cin>>user_1;
                no_of_friends(user_1,db,adj);
                break;
                
            //Display Friends List
            case 4:
                cout<<"\nEnter the user name : ";
                cin>>user_1;
                display_friends_list(user_1,db,temp_db,adj);
                break;
                
            //Recommend new Friends
            case 5:
                cout<<"\nEnter the user name : ";
                cin>>user_1;
                recommend(user_1,db,temp_db,adj);
                break;
                
            //Check Connections Strength(Dijkstra's algorithm)
            case 6:
                dijkstra(db.size(),db,g,temp_db);
                break;
                
            //Users with maximum number of Friends
            case 7:
                max_friends(adj,temp_db);
                break;
                
            //Users with minimum number of Friends
            case 8:
                min_friends(adj,temp_db);
                break;
            default:
                exit(0);
        }
        
    }
    
    return 0;
}