#include<iostream>
#include<string>
#include<vector>

using namespace std;


class Task
{
public: 
    Task(string keep_list_name,string keep_name , unsigned int keep_Time,unsigned int keep_priority, string keep_description)
    {
    name=keep_name;
    list=keep_list_name;
    estimatedTime=keep_Time;
    priority=keep_priority;
    description=keep_description;
    is_deleted=false;
    is_compilited=false;
    assigned_to = "Unassigned";
    }
    void change_list_name(string listname)
    {
        list = listname;
    }
    string return_name_task()
    {
        return name;
    }
    string return_name_list()
    {
        return list;
    }
    unsigned int return_estimatedTime()
    {
        return estimatedTime;
    }
    unsigned int return_priority()
    {
        return priority;
    }
    void change_estimatedTime(unsigned int new_estimatedTime)
    {
    estimatedTime=new_estimatedTime;
    }
    void change_priority(unsigned int new_priority)
    {
    priority=new_priority;
    }
    void change_description(string new_description)
    {
    description=new_description;
    }
    string return_description()
    {
        return description;
    }
    void delete_task()
    {
        is_deleted=true;
    }
    bool delete_status_task()
    {
        return is_deleted;
    }
    void compilit_task()
    {
        is_compilited=true;
    }
    bool compilit_status_tasks()
    {
        return is_compilited;
    }
    void assign_to(string n)
    {
        assigned_to = n;
    }
    string return_assigned_to()
    {
        return assigned_to;
    }
    
private:
    bool is_deleted;
    bool is_compilited;
    string name;
    string list;
    unsigned int estimatedTime;
    unsigned int priority;
    string description;
    string assigned_to;

};


class User
{
public:
    User(string name)
    {
        username=name;
    }
    string return_username()
    {
        return username;
    }
    void push_back_tasks(Task* assign_task)
    {
        tasks_of_user.push_back(assign_task);
    }
    int number_of_tasks() { return tasks_of_user.size(); }
    int return_sum_of_times()
    {
        int x=0;
        for(int i=0;i<tasks_of_user.size();i++)
        {
            x+=tasks_of_user[i]->return_estimatedTime();
        }
        return x;
    }

    int return_sum_of_remain_times()
    {
        int x=0;
        for(int i=0;i<tasks_of_user.size();i++)
        {  
            if(tasks_of_user[i]->compilit_status_tasks()!= true)
            {
            x+=tasks_of_user[i]->return_estimatedTime();
            }
        }
        return x;
    }
    int return_sum_of_tasks_time()
    {
        int x=0;
        for(int i=0;i<tasks_of_user.size();i++)
        {  
            x+=tasks_of_user[i]->return_estimatedTime();
        }
        return x;
    }
    vector<Task*> return_tasks_of_user()
    {

        return tasks_of_user;
    }
private:
    string username;
    vector<Task*>tasks_of_user;
};

class List
{
public:

    List(string keep_name)
    {
        name=keep_name;
        is_deleted = false;
    }
    string return_name_list()
    {
        return name;
    }
    void delete_list()
    {
        is_deleted=true;
    }
    bool delete_status()
    {
        return is_deleted;
    }
    void add_task_list(Task* new_task)
    {
        tasks_of_list.push_back(new_task);
    }
    void delete_task_list(string task_name)
    {
        for(int i=0;i<tasks_of_list.size();i++)
        {
            if(tasks_of_list[i]->return_name_task()==task_name)
                tasks_of_list[i]->delete_task();
        }
    }
    bool delete_status_task()
    {
        return is_deleted_task;
    }
    vector<Task*>return_tasks_of_list()
    {
        return tasks_of_list;
    }
private:
    bool is_deleted;
    bool is_deleted_task;
    string name;
    vector<Task*>tasks_of_list;

};


class UTrelloInterface
{
public:
	UTrelloInterface();

	string addUser(string username);
	string addTask(string list,string name, unsigned int estimatedTime, unsigned int priority, string description);
	string editTask(string task, unsigned int estimatedTime, unsigned int priority, string description);
	string deleteTask(string task);
	string assignTask(string task,string user);
	string moveTask(string task,string list);
	string completeTask(string task);
    string printTask(string task);
	string addList(string name);
	string deleteList(string list);
	string printList(string list);
	string printUserTasks(string user);
	string printUserUnfinishedTasks(string user);
	int printTotalEstimatedTime();
	int printTotalRemainingTime();
    int printUserWorkload(string user);
	string printUsersByWorkload();
	string printUsersByPerformance();
    string printAllLists();
    string printUnassignedTasksByPriority();
	string printAllUnfinishedTasksByPriority();
    void sort_tasks_by_priority();
    void sort_users_by_time();
    void sort_users_by_estimatedtime();
    bool is_in_tasks(vector<Task*>t,Task* t2);
    bool is_in_users(vector<User*>u,User* u2);
    private:
    vector<User*> Users;
    vector<User*> Sorted_Users;
    vector<User*> Sorted_Users_estimatedtime;
    vector<List*> Lists;
    vector<Task*> Tasks;
    vector<Task*> Sorted_Tasks;
    vector<Task*>tasks_of_user;
    vector<Task*>tasks_remain;
};
UTrelloInterface::UTrelloInterface(){}
bool UTrelloInterface::is_in_users(vector<User*>u,User* u2)
{
    for(int i=0;i<u.size();i++)
    if(u[i]->return_username() == u2->return_username())
        return true;
    return false;

}
void UTrelloInterface::sort_users_by_estimatedtime()
{
    for(int i=0;i<Sorted_Users_estimatedtime.size();i++)
        Sorted_Users_estimatedtime.pop_back();
    vector<int> times;
    for(int i=0;i<Users.size();i++)
        times.push_back(Users[i]->return_sum_of_times());
    for(int i=1;i<times.size();i++)
    {
        int j=i+1;
        int keep = times[j];
        while(j>1 && keep<=times[j-1])
        {
            times[j]=times[j-1];
            j--;
        }
        times[j] = keep;
    }
    for(int i=0;i<times.size();i++)
    {
        for(int j=0;j<Users.size();j++)
        {
            if(times[i] == Users[j]->return_sum_of_times() && !is_in_users(Sorted_Users_estimatedtime,Users[j]))
            {
                Sorted_Users_estimatedtime.push_back(Users[j]);
            }
        }
    }
}

void UTrelloInterface::sort_users_by_time()
{
    for(int i=0;i<Sorted_Users.size();i++)
        Sorted_Users.pop_back();
    vector<int> nums;
    for(int i=0;i<Users.size();i++)
        nums.push_back(Users[i]->number_of_tasks());
    for(int i=1;i<nums.size();i++)
    {
        int j=i+1;
        int keep = nums[j];
        while(j>1 && keep<=nums[j-1])
        {
            nums[j]=nums[j-1];
            j--;
        }
        nums[j] = keep;
    }
    for(int i=0;i<nums.size();i++)
    {
        for(int j=0;j<Users.size();j++)
        {
            if(nums[i] == Users[j]->number_of_tasks() && !is_in_users(Sorted_Users,Users[j]))
            {
                Sorted_Users.push_back(Users[j]);
            }
        }
    }
}
bool UTrelloInterface::is_in_tasks(vector<Task*> t,Task* t2)
{
    for(int i=0;i<t.size();i++)
        if(t[i]->return_name_task() == t2->return_name_task())
            return true;
    return false;
}
void UTrelloInterface::sort_tasks_by_priority()
{
    for(int i=0;i<Sorted_Tasks.size();i++)
        Sorted_Tasks.pop_back();
    vector<int> priorities;
    for(int i=0;i<Tasks.size();i++)
        priorities.push_back(Tasks[i]->return_priority());
    for(int i=1;i<priorities.size();i++)
    {
        int j=i+1;
        int keep = priorities[j];
        while(j>1 && keep<=priorities[j-1])
        {
            priorities[j]=priorities[j-1];
            j--;
        }
        priorities[j] = keep;
    }
    for(int i=0;i<priorities.size();i++)
    {
        for(int j=0;j<Tasks.size();j++)
        {
            if(priorities[i] == Tasks[j]->return_priority() && !is_in_tasks(Sorted_Tasks,Tasks[j]))
            {
                Sorted_Tasks.push_back(Tasks[j]);
            }
        }
    }
}

string UTrelloInterface::addUser(string username)
{
    for(int i=0;i<Users.size();i++)
    {
        if(Users[i]->return_username()==username)
        {
            return "User already exists";
        }
    }
    User* new_user= new User(username);
    Users.push_back(new_user);
    return"Success";
}
string UTrelloInterface::addList(string name)
{
    for(int i=0;i<Lists.size();i++)
    {
        if(Lists[i]->return_name_list()==name)
        {
            return "List already exists";
        }
    }
    List* new_list= new List(name);
    Lists.push_back(new_list);
    return"Success";
}
string UTrelloInterface::addTask(string list, string name,
    unsigned int estimatedTime, unsigned int priority,string description)
    {
        List* keep_list;
        for(int i=0;i<Lists.size();i++)
        {
            if(Lists[i]->return_name_list()==list)
            {
                keep_list = Lists[i];
            }
        }
        if(keep_list==NULL)
            return "List does not exist";
        for(int i=0;i<Tasks.size();i++)
        {
            if(Tasks[i]->return_name_task()==name)
            {
                return "Task already exists";
            }
        }
        Task* new_task= new Task(list,name,estimatedTime,priority,description);
        Tasks.push_back(new_task);
        keep_list->add_task_list(new_task);
        return "Success";
    }

string UTrelloInterface::deleteList(string list)
{
        for(int i=0;i<Lists.size();i++)
        {
            if(Lists[i]->return_name_list()==list && Lists[i]->delete_status()!= true)
            {
                Lists[i] ->delete_list();
                return "Success";
            }
        }
        return "List does not exist";
}
string UTrelloInterface::deleteTask(string task)
{
   for(int i=0;i<Tasks.size();i++)
        {
            if(Tasks[i]->return_name_task()==task && Tasks[i]->delete_status_task()!= true)
            {
                Tasks[i]->delete_task();
                return "Success";
            }
            
        }
       return "Task does not exist"; 
}


string UTrelloInterface::assignTask(string task,string user)
{
    Task* keep_task;

    for(int j=0;j<Tasks.size();j++)
    {
        if(Tasks[j]->return_name_task()==task)
        {
            keep_task = Tasks[j];
        }
    }
    if(keep_task == NULL)
        return "Task does not exist";
    
    for(int i=0;i<Users.size();i++)
    {
        if(Users[i]->return_username()==user )
        {
            keep_task->assign_to(Users[i]->return_username());
            Users[i]->push_back_tasks(keep_task);
            return "Success";
        }
    }
    return" User does not exist";

}


string UTrelloInterface::editTask(string task, unsigned int estimatedTime,
    unsigned int priority, string description)
{
    Task* keep_task;

    for(int j=0;j<Tasks.size();j++)
    {
        if(Tasks[j]->return_name_task()==task)
        {
            keep_task = Tasks[j];
        }
    }
    if(keep_task == NULL)
        return "Task does not exist";
    
    if(keep_task->return_estimatedTime()!=estimatedTime)
        keep_task->change_estimatedTime(estimatedTime);
    if(keep_task->return_priority()!=priority)
        keep_task->change_priority(priority);   
    if(keep_task->return_description()!=description)
        keep_task->change_description(description);
        return "Success";
}


string UTrelloInterface::moveTask(string task, string list)
{
    List* keep_list;
    for(int j=0;j<Lists.size();j++)
    {
        if(Lists[j]->return_name_list()==list)
        {
            keep_list = Lists[j];
        }
    }
    if(keep_list == NULL)
        return "Lists does not exist";
    
    Task* keep_task;
    for(int j=0;j<Tasks.size();j++)
    {
        if(Tasks[j]->return_name_task()==task)
        {
            keep_task = Tasks[j];
        }
    }
    if(keep_task == NULL)
        return "Task does not exist";
    
    keep_task->change_list_name(list);
    keep_list->add_task_list(keep_task);
    return "Success";
}


string UTrelloInterface::completeTask(string task)
{
    for(int i=0;i<Tasks.size();i++)
        {
            if(Tasks[i]->return_name_task()==task &&Tasks[i]->compilit_status_tasks()!= true)
            {
                cout<<Tasks[i]->return_name_task()<<endl;
                Tasks[i] ->compilit_task();
                return "Success";
            }
            
        }
       return "Task does not exist"; 
    
}

int UTrelloInterface::printTotalEstimatedTime()
{
   vector<int>majmou;

    for(int i=0;i<Users.size();i++)
    {
        majmou.push_back(Users[i]->return_sum_of_times());
    }

    int max_majmou=0;
    max_majmou=majmou[0];
    for(int k=1;k<majmou.size();k++)
    {
        if(majmou[k]>max_majmou)
            max_majmou = majmou[k];
    }
    return max_majmou;
}

int UTrelloInterface::printTotalRemainingTime()
{
    vector<int>majmou;

    for(int i=0;i<Users.size();i++)
    {
        majmou.push_back(Users[i]->return_sum_of_remain_times());
    }

    int max_majmou=0;
    max_majmou=majmou[0];
    for(int k=1;k<majmou.size();k++)
    {
        if(majmou[k]>max_majmou)
            max_majmou = majmou[k];
    }
    return max_majmou;

}
int UTrelloInterface::printUserWorkload(string user)
{
    int majmou;
    for(int i=0;i<Users.size();i++)
    {
        if(Users[i]->return_username()==user)
        {   majmou=Users[i]->return_sum_of_tasks_time();
            return majmou;
        }
    }
    return 0;
}

string UTrelloInterface::printTask(string task)
{
    for(int i=0;i<Tasks.size();i++)
    {
        if(Tasks[i]->return_name_task()==task)
        {
            cout<<Tasks[i]->return_name_task()<<endl;
            cout<<Tasks[i]->return_description()<<endl;
            cout<<"Priority: "<<Tasks[i]->return_priority()<<endl;
            cout<<"Estimated Time: "<<Tasks[i]->return_estimatedTime()<<endl;
            for(int j=0;j<Users.size();j++)
            {
                for(int k=0;k<Users[j]->return_tasks_of_user().size();k++)
                {
                if(Tasks[k]->return_name_task()==task)
                {
                    cout<<"Assigned to ";
                    return Users[j]->return_username();
                }
                else
                return "Unassigned";
                }
            }
        
        }
    }
   return "Task does not exist";
}

string UTrelloInterface::printList(string list)
{
    string data="list "+list+'\n';
    for(int i=0;i<Lists.size();i++)
    {
        if(Lists[i]->return_name_list()==list)
        {
            for(int j=0;j<Lists[i]->return_tasks_of_list().size();j++)
            {
                data+= to_string(Lists[i]->return_tasks_of_list()[j]->return_priority())+" | "+Lists[i]->return_tasks_of_list()[j]->return_name_task()+" | "+Lists[i]->return_tasks_of_list()[j]->return_assigned_to() +" | "+ to_string(Lists[i]->return_tasks_of_list()[j]->return_estimatedTime())+"h"+'\n';
            }
            return data;
        }
    }
    return  " List does not exist ";
}
string UTrelloInterface::printAllLists()
{
    string data="";
    for(int i=0;i<Lists.size();i++)
    {
        int x=0;
        data += "list "+Lists[i]->return_name_list()+'\n';
        for(int j=0;j<Lists[i]->return_tasks_of_list().size();j++)
        {
            if(Lists[i]->return_tasks_of_list()[j]->return_name_list()== Lists[i]->return_name_list() && Lists[i]->return_tasks_of_list()[j]->delete_status_task()!=true)
                {data+= to_string(Lists[i]->return_tasks_of_list()[j]->return_priority())+" | "+Lists[i]->return_tasks_of_list()[j]->return_name_task()+" | "+Lists[i]->return_tasks_of_list()[j]->return_assigned_to() +" | "+ to_string(Lists[i]->return_tasks_of_list()[j]->return_estimatedTime())+"h"+'\n';
        x=1;}
        }
        if(x==1)
        data+='\n';
    }

    return data;
}
string UTrelloInterface::printUserTasks(string user)
{
    User* keep_user;
    for(int i=0;i<Users.size();i++)
    {
        if(Users[i]->return_username()==user)
        {
            keep_user = Users[i];  
        }
    }
    if(keep_user == NULL)
        return"User does not exist";
    string data="";
    for(int j=0;j<keep_user->return_tasks_of_user().size();j++)
    {
        if(keep_user->return_tasks_of_user()[j]->delete_status_task()!=true)
        data+= to_string(keep_user->return_tasks_of_user()[j]->return_priority())+" | "+keep_user->return_tasks_of_user()[j]->return_name_task()+" | "+keep_user->return_tasks_of_user()[j]->return_assigned_to() +" | "+ to_string(keep_user->return_tasks_of_user()[j]->return_estimatedTime())+"h"+'\n';
    }
    return data;
}
string UTrelloInterface::printUserUnfinishedTasks(string user)
{
    User* keep_user;
    for(int i=0;i<Users.size();i++)
    {
        if(Users[i]->return_username()==user)
        {
            keep_user = Users[i];  
        }
    }
    if(keep_user == NULL)
        return"User does not exist";
    string data="";
    for(int j=0;j<keep_user->return_tasks_of_user().size();j++)
    {
        if(keep_user->return_tasks_of_user()[j]->compilit_status_tasks()!=true &&keep_user->return_tasks_of_user()[j]->delete_status_task()!=true)
        data+= to_string(keep_user->return_tasks_of_user()[j]->return_priority())+" | "+keep_user->return_tasks_of_user()[j]->return_name_task()+" | "+keep_user->return_tasks_of_user()[j]->return_assigned_to() +" | "+ to_string(keep_user->return_tasks_of_user()[j]->return_estimatedTime())+"h"+'\n';
    }
    return data;
}
string UTrelloInterface::printUnassignedTasksByPriority()
{
    string data="";
    sort_tasks_by_priority();
    for(int i=0;i<Sorted_Tasks.size();i++)
    {
        if(Sorted_Tasks[i]->return_assigned_to()=="Unassigned" && Sorted_Tasks[i]->delete_status_task()!=true)
            data+= to_string(Sorted_Tasks[i]->return_priority())+" | "+Sorted_Tasks[i]->return_name_task()+" | "+Sorted_Tasks[i]->return_assigned_to() +" | "+ to_string(Sorted_Tasks[i]->return_estimatedTime())+"h"+'\n';
    }
    return data;
}
string UTrelloInterface::printAllUnfinishedTasksByPriority()
{
    string data="";
    sort_tasks_by_priority();
    for(int i=0;i<Sorted_Tasks.size();i++)
    {
        if(Sorted_Tasks[i]->compilit_status_tasks()!=true && Sorted_Tasks[i]->delete_status_task()!=true)
            data+= to_string(Sorted_Tasks[i]->return_priority())+" | "+Sorted_Tasks[i]->return_name_task()+" | "+Sorted_Tasks[i]->return_assigned_to() +" | "+ to_string(Sorted_Tasks[i]->return_estimatedTime())+"h"+'\n';
    }
    return data;
}
string UTrelloInterface::printUsersByWorkload()
{
    string data="";
    sort_users_by_time();
    for(int i=0;i<Sorted_Users.size();i++)
    {
        data+=Sorted_Users[i]->return_username() + '\n';
    }
    return data;
}
string UTrelloInterface::printUsersByPerformance()
{
    string data="";
    sort_users_by_estimatedtime();
    for(int i=Sorted_Users_estimatedtime.size()-1;i>=0;i--)
    {
        data+=Sorted_Users_estimatedtime[i]->return_username() + '\n';
    }
    return data;

}

int main()
{
	UTrelloInterface interface;

	cout << interface.addUser("Zhivar") << endl;

	cout << interface.addUser("Amir") << endl;

	cout << interface.addUser("Bardia") << endl;

	cout << interface.addList("Code") << endl;

	cout << interface.addList("Description") << endl;

	cout << interface.addList("Misc") << endl;

    cout << interface.addTask("Code", "Do Everything", 12, 1, "Write the whole code") << endl;

    cout << interface.editTask("Do Everything", 12, 10, "Write the whole code") << endl;

    cout << interface.assignTask("Do Everything", "Bardia") << endl;

    cout << interface.printTask("Do Everything") << endl;

    cout << interface.addTask("Code", "Destroy code formatting", 1, 2, "Rewrite the whole code in a worse format") << endl;

	cout << interface.assignTask("Destroy code formatting", "Zhivar") << endl;

	cout << interface.addTask("Description", "Write Description", 3, 1, "Write the damn description") << endl;

	cout << interface.assignTask("Write Description", "Amir") << endl;

	cout << interface.addTask("Misc", "Upload Assignment", 1, 1, "Upload it") << endl;

	cout << interface.completeTask("Do Everything") << endl;

	cout << interface.deleteTask("Upload Assignment") << endl;

    cout << interface.printUserWorkload("Amir")<<endl;

	cout << interface.addTask("Misc", "Have fun", 10, 2, "Just do it") << endl;

	cout << interface.moveTask("Have fun", "Code") << endl;

    cout << interface.printTotalEstimatedTime()<<endl;

    cout << interface.printTotalRemainingTime()<<endl;

	cout << interface.printTask("Have fun") << endl;

    cout << interface.printList("Code") << endl;

    cout << interface.printAllLists() << endl;

    cout << interface.printUserTasks("Amir") << endl;

    cout << interface.printUserUnfinishedTasks("Amir")<<endl;

    cout << interface.printUnassignedTasksByPriority() << endl;
	
    cout << interface.printAllUnfinishedTasksByPriority() << endl;

    cout << interface.printUsersByWorkload() << endl;

	cout << interface.printUsersByPerformance() << endl;

    return 0;
}
