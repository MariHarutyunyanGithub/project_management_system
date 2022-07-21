#ifndef PROTOTYPE_HPP
#define PROTOTYPE_HPP
#include <fstream>
#include <string>

std::fstream file;
std::fstream iofile;
struct Date
{
  int m_year;
  int m_month;
  int m_day;
}date;

class Project
{
  public:  
    void create_project();                       
    void edit_project(std::string);
    void edit_project_name(std::string); 
    void search_project(std::string); 
    void remove_project(std::string); 
    void set_deadline(Date);   
    void set_name(std::string);
    std::string get_name()const;                                             
  private:
    std::string project_name{};
    Date m_deadline{};    
}project;

class Task
{
public:
    void search_task(std::string);        
    void remove_task(std::string); 
    void edit_task(std::string);                         
    void create_task();                                                     
    void set_deadline(Date);               
    void set_name(std::string);
    void set_proj_name(std::string);  
    void set_state(); 
    void set_assignee_name(std::string);             
    std::string get_name()const;  
    std::string get_proj_name()const;
    std::string get_state()const; 
    std::string get_assignee_name();           
 private:                          
    std::string task_name{};
    std::string project_name{};
    std::string assignee{};
    std::string state {"to do"};
    std::string assignee_name{};
    Date m_deadline{};
}task;

std::string date_to_string(Date); 
void project_steps();   
void task_steps();                    
void project_functions(short);                               
void task_functions(short);  
void exit_from_program(); 
void edit_deadline(std::string);  

#endif//PROTOTYPE_HPP