//
// Created by nikolay on 6/27/22.
//

#ifndef PMS_PMS_H
#define PMS_PMS_H
#include<string>
#include<vector>
#include <fstream>

class Date
{
private:
    int m_year;
    int m_month;
    int m_day;
public:
    Date() = default;
    Date(int year, int month, int day);
    void setYear(int year);
    void setMonth(int month);
    void setDay(int day);
    int getYear() const;
    int getMonth() const;
    int getDay() const;
    std::string Display() const;

};



class Task
{
private:
    std::string m_name;
    std::string m_assignee;
    Date m_deadline;
    std::string m_state;


public:
    Task() = default;
    Task(std::string name);
    void setName(std::string name);
    void setAssignee(std::string assignee);
    std::string getName() const;
    std::string getAssignee() const;
    void setDeadline(int day, int month, int year);
    std::string getDeadline() const;
    void setState(std::string state);
    std::string getState() const;
    void show_task();

};

class Project
{
private:
    std::string m_name;
    std::vector<Task> m_tasks;
public:
    Project() = default;
    Project(std::string name);
public:
    void setName(std::string name);
    std::string getName() const;
    std::string getTaskLine();
    int getTaskCount() const;
    void addTask(Task& task);
    void removeTask(const int);
    void showProject();
    void setTask(int);
};

class PMS
{
private:
    std::vector<Project> m_projs;
public:
    PMS() = default;
    PMS(std::ifstream &fin);

    void add_new_project();
    void add_new_task_to_the_project();
    void add_projects_to_file(std::ostream &);
    void edit_project();
    void edit_project_task();
    void remove_project();
    void remove_project_task();
    void show_projec_information();
    void list_of_projects_and_tasks();
};


#endif //PMS_PMS_H
