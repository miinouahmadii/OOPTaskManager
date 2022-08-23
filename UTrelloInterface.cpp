#include<iostream>
#include<string>
#include<vector>
#include"UTrelloInterface.hpp"
#include"Task.hpp"
#include"List.hpp"
#include"User.hpp"


UTrelloInterface::UTrelloInterface() {}
bool UTrelloInterface::is_in_users(std::vector<User*>u,User* u2)
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
    std::vector<int> times;
    for(int i=0;i<Users.size();i++)
        times.push_back(Users[i]->return_sum_of_times());
    for(int i=1;i<times.size();i++)
    {
        int j=i+1;
        int keep = times[j];
        while(j>1 && keep<=times[j-1])
        {
            times[j] = times[j-1];
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
    for(int i=0;i<Sorted_U sers.size();i++)
        Sorted_Users.pop_back();
    std::vector<int> nums;
    for(int i=0;i<Users.size();i++)
        nums.push_back(Users[i]->number_of_tasks());
    for(int i=1;i<nums.size();i++)
    {
        int j=i+1;
        int keep = nums[j];
        while(j>1 && keep<=nums[j-1])
        {
            nums[j] = nums[j-1];
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
bool UTrelloInterface::is_in_tasks(std::vector<Task*> t,Task* t2)
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
    std::vector<int> priorities;
    for(int i=0;i<Tasks.size();i++)
        priorities.push_back(Tasks[i]->return_priority());
    for(int i=1;i<priorities.size();i++)
    {
        int j=i+1;
        int keep = priorities[j];
        while(j>1 && keep <= priorities[j-1])
        {
            priorities[j] = priorities[j-1];
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
std::string UTrelloInterface::addUser(std::string username)
{
    for(int i=0;i<Users.size();i++)
    {
        if(Users[i]->return_username()==username)
        {
            return "User already exists";
        }
    }
    User* new_user = new User(username);
    Users.push_back(new_user);
    return"Success";
}
std::string UTrelloInterface::addList(std::string name)
{
    for(int i=0;i<Lists.size();i++)
    {
        if(Lists[i]->return_name_list() == name)
        {
            return "List already exists";
        }
    }
    List* new_list= new List(name);
    Lists.push_back(new_list);
    return"Success";
}
std::string UTrelloInterface::addTask(std::string list, std::string name,
    unsigned int estimatedTime, unsigned int priority,std::string description)
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
        Task* new_task = new Task(list,name,estimatedTime,priority,description);
        Tasks.push_back(new_task);
        keep_list->add_task_list(new_task);
        return "Success";
    }

std::string UTrelloInterface::deleteList(std::string list)
{
        for(int i=0;i<Lists.size();i++)
        {
            if(Lists[i]->return_name_list()==list && Lists[i]->delete_status()!= true)
            {
                Lists[i]->delete_list();
                return "Success";
            }
        }
        return "List does not exist";
}
std::string UTrelloInterface::deleteTask(std::string task)
{
   for(int i=0;i<Tasks.size();i++)
        {
            if(Tasks[i]->return_name_task() == task && Tasks[i]->delete_status_task()!= true)
            {
                Tasks[i]->delete_task();
                return "Success";
            }
            
        }
       return "Task does not exist"; 
}
std::string UTrelloInterface::assignTask(std::string task,std::string user)
{
    Task* keep_task;

    for(int j=0;j<Tasks.size();j++)
    {
        if(Tasks[j]->return_name_task() == task)
        {
            keep_task = Tasks[j];
        }
    }
    if(keep_task == NULL)
        return "Task does not exist";
    
    for(int i=0;i<Users.size();i++)
    {
        if(Users[i]->return_username() == user )
        {
            keep_task->assign_to(Users[i]->return_username());
            Users[i]->push_back_tasks(keep_task);
            return "Success";
        }
    }
    return" User does not exist";

}
std::string UTrelloInterface::editTask(std::string task, unsigned int estimatedTime,
    unsigned int priority, std::string description)
{
    Task* keep_task;

    for(int j=0;j<Tasks.size();j++)
    {
        if(Tasks[j]->return_name_task() == task)
        {
            keep_task = Tasks[j];
        }
    }
    if(keep_task == NULL)
        return "Task does not exist";
    
    if(keep_task->return_estimatedTime()!= estimatedTime)
        keep_task->change_estimatedTime(estimatedTime);
    if(keep_task->return_priority()!= priority)
        keep_task->change_priority(priority);   
    if(keep_task->return_description()!= description)
        keep_task->change_description(description);
        return "Success";
}
std::string UTrelloInterface::moveTask(std::string task,std::string list)
{
    List* keep_list;
    for(int j=0;j<Lists.size();j++)
    {
        if(Lists[j]->return_name_list() == list)
        {
            keep_list = Lists[j];
        }
    }
    if(keep_list == NULL)
        return "Lists does not exist";
    
    Task* keep_task;
    for(int j=0;j<Tasks.size();j++)
    {
        if(Tasks[j]->return_name_task() == task)
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
std::string UTrelloInterface::completeTask(std::string task)
{
    for(int i=0;i<Tasks.size();i++)
        {
            if(Tasks[i]->return_name_task() == task &&Tasks[i]->compilit_status_tasks()!= true)
            {
                cout<<Tasks[i]->return_name_task()<<std::endl;
                Tasks[i] ->compilit_task();
                return "Success";
            }
            
        }
       return "Task does not exist"; 
    
}
int UTrelloInterface::printTotalEstimatedTime()
{
    std::vector<int>sum;

    for(int i=0;i<Users.size();i++)
    {
        sum.push_back(Users[i]->return_sum_of_times());
    }

    int max_sum=0;
    max_sum=sum[0];
    for(int k=1;k<sum.size();k++)
    {
        if(sum[k] > max_sum)
            max_sum = sum[k];
    }
    return max_sum;
}
int UTrelloInterface::printTotalRemainingTime()
{
    std::vector<int>sum;

    for(int i=0;i<Users.size();i++)
    {
        sum.push_back(Users[i]->return_sum_of_remain_times());
    }

    int max_sum=0;
    max_sum=sum[0];
    for(int k=1;k<sum.size();k++)
    {
        if(sum[k] > max_sum)
            max_sum = sum[k];
    }
    return max_sum;

}
int UTrelloInterface::printUserWorkload(std::string user)
{
    int sum;
    for(int i=0;i<Users.size();i++)
    {
        if(Users[i]->return_username() == user)
        {   sum=Users[i]->return_sum_of_tasks_time();
            return sum;
        }
    }
    return 0;
}
std::string UTrelloInterface::printTask(std::string task)
{
    for(int i=0;i<Tasks.size();i++)
    {
        if(Tasks[i]->return_name_task() == task)
        {
            cout<<Tasks[i]->return_name_task()<<std::endl;
            cout<<Tasks[i]->return_description()<<std::endl;
            cout<<"Priority: "<<Tasks[i]->return_priority()<<std::endl;
            cout<<"Estimated Time: "<<Tasks[i]->return_estimatedTime()<<std::endl;
            for(int j=0;j<Users.size();j++)
            {
                for(int k=0;k<Users[j]->return_tasks_of_user().size();k++)
                {
                if(Tasks[k]->return_name_task() == task)
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
std::string UTrelloInterface::printList(std::string list)
{
    std::string data="list "+list+'\n';
    for(int i=0;i<Lists.size();i++)
    {
        if(Lists[i]->return_name_list() == list)
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
std::string UTrelloInterface::printAllLists()
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
        data += '\n';
    }
    return data;
}
std::string UTrelloInterface::printUserTasks(std::string user)
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
    std::string data="";
    for(int j=0;j<keep_user->return_tasks_of_user().size();j++)
    {
        if(keep_user->return_tasks_of_user()[j]->delete_status_task()!=true)
        data+= to_string(keep_user->return_tasks_of_user()[j]->return_priority())+" | "+keep_user->return_tasks_of_user()[j]->return_name_task()+" | "+keep_user->return_tasks_of_user()[j]->return_assigned_to() +" | "+ to_string(keep_user->return_tasks_of_user()[j]->return_estimatedTime())+"h"+'\n';
    }
    return data;
}
std::string UTrelloInterface::printUserUnfinishedTasks(std::string user)
{
    User* keep_user;
    for(int i=0;i<Users.size();i++)
    {
        if(Users[i]->return_username() == user)
        {
            keep_user = Users[i];  
        }
    }
    if(keep_user == NULL)
        return"User does not exist";
    std::string data = "";
    for(int j=0;j<keep_user->return_tasks_of_user().size();j++)
    {
        if(keep_user->return_tasks_of_user()[j]->compilit_status_tasks()!= true &&keep_user->return_tasks_of_user()[j]->delete_status_task()!=true)
        data += to_string(keep_user->return_tasks_of_user()[j]->return_priority())+" | "+keep_user->return_tasks_of_user()[j]->return_name_task()+" | "+keep_user->return_tasks_of_user()[j]->return_assigned_to() +" | "+ to_string(keep_user->return_tasks_of_user()[j]->return_estimatedTime())+"h"+'\n';
    }
    return data;
}
std::string UTrelloInterface::printUnassignedTasksByPriority()
{
    std::string data="";
    sort_tasks_by_priority();
    for(int i=0;i<Sorted_Tasks.size();i++)
    {
        if(Sorted_Tasks[i]->return_assigned_to() == "Unassigned" && Sorted_Tasks[i]->delete_status_task()!= true)
            data+= to_string(Sorted_Tasks[i]->return_priority())+" | "+Sorted_Tasks[i]->return_name_task()+" | "+Sorted_Tasks[i]->return_assigned_to() +" | "+ to_string(Sorted_Tasks[i]->return_estimatedTime())+"h"+'\n';
    }
    return data;
}
std::string UTrelloInterface::printAllUnfinishedTasksByPriority()
{
    std::string data="";
    sort_tasks_by_priority();
    for(int i=0;i<Sorted_Tasks.size();i++)
    {
        if(Sorted_Tasks[i]->compilit_status_tasks()!= true && Sorted_Tasks[i]->delete_status_task()!= true)
            data+= to_string(Sorted_Tasks[i]->return_priority())+" | "+Sorted_Tasks[i]->return_name_task()+" | "+Sorted_Tasks[i]->return_assigned_to() +" | "+ to_string(Sorted_Tasks[i]->return_estimatedTime())+"h"+'\n';
    }
    return data;
}
std::string UTrelloInterface::printUsersByWorkload()
{
    std::string data="";
    sort_users_by_time();
    for(int i=0;i<Sorted_Users.size();i++)
    {
        data+=Sorted_Users[i]->return_username() + '\n';
    }
    return data;
}
std::string UTrelloInterface::printUsersByPerformance()
{
    std::string data="";
    sort_users_by_estimatedtime();
    for(int i=Sorted_Users_estimatedtime.size()-1;i>=0;i--)
    {
        data+=Sorted_Users_estimatedtime[i]->return_username() + '\n';
    }
    return data;

}
