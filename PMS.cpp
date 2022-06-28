//
// Created by nikolay on 6/27/22.
//
#include <iostream>
#include "PMS.h"

//Date Def-n
Date::Date(int year, int month, int day)
        : m_year(year), m_month(month), m_day(day)
{
}

void Date::setYear(int year)
{
    m_year = year;
}

void Date::setMonth(int month)
{
    if(month > 12)
        std::cout << "Invalid form\n";
    else m_month = month;
}

void Date::setDay(int day)
{
    if(day > 31)
        std::cout << "Invalid form\n";
    else m_day = day;
}

int Date::getYear() const
{
    return m_year;
}
int Date::getMonth() const
{
    return m_month;
}
int Date::getDay() const
{
    return m_day;
}
std::string Date ::Display() const
{
    std::string line = std::to_string(m_day) + ':' + std::to_string(m_month) + ':' + std::to_string(m_year) + '\n';
    return line;
}


//Project Def-n
Project::Project(std::string name)
        : m_name(name)
{}
void Project::setName(std::string name)
{
    m_name = name;
}
std::string Project::getName() const
{
    return m_name;
}

std::string Project::getTaskLine()
{
    std::string info;
    for(std::size_t i{}; i<m_tasks.size(); ++i)
    {
        info += "Task: " + m_tasks[i].getName() + " Assignee: " + m_tasks[i].getAssignee()
                + " State: " + m_tasks[i].getState() + " Deadline: " + m_tasks[i].getDeadline() + "\n";
    }
    return info;
}

int Project::getTaskCount() const
{
    return m_tasks.size();
}

void Project::addTask(Task &task)
{
    m_tasks.push_back(task);
}

void Project::removeTask(int index)
{
    int i{};
    for(auto it = m_tasks.begin(); it!= m_tasks.end(); ++it)
    {
        if(i == index - 1)
        {
            m_tasks.erase(it);
            break;
        }
        ++i;
    }
}

void Project::showProject()
{
   std::cout << "Project: " << m_name << std::endl;
    for(int i = 0; i < m_tasks.size(); ++i){
        std::cout << "[" << i+1 << "]";
        m_tasks[i].show_task();
    }
}

void Project::setTask(int index)
{
    std::string token;
    std::cout << std::endl << "You can pass changing the element by writing 'pass'" << std::endl;
    std::cout << std::endl << "Enter Task's name: ";
    std::getline(std::cin, token);
    if(token.compare("pass") != 0)
    {
        m_tasks[index].setName(token);
    }
    std::cout << "Enter Task's state";
    std::getline(std::cin, token);
    if(token.compare("pass") != 0)
    {
        m_tasks[index].setState(token);
    }
    std::cout << "Enter Task's Assignee";
    std::getline(std::cin, token);
    if(token.compare("pass") != 0)
    {
        m_tasks[index].setAssignee(token);
    }
    std::cout << "Enter Task's Deadline's day, month, and year respectively";
    int d,m,y;
    std::cin >> d >> m >> y;
    m_tasks[index].setDeadline(d,m,y);
}

//Task Def-n
Task :: Task(std::string name)
        : m_name(name)
{
}
void Task::setName(std::string name)
{
    m_name = name;
}

void Task::show_task(){
    std::cout << "task: " << m_name << "   status: " << m_state << "   assignee: " << m_assignee << "   deadline: " << m_deadline.Display();
    std::cout << std::endl;
}

void Task::setAssignee(std::string assignee)
{
    m_assignee = assignee;
}
std::string Task::getName() const
{
    return m_name;
}
std::string Task::getAssignee() const
{
    return m_assignee;
}
void Task::setDeadline(int day, int month, int year )
{
    m_deadline.setDay(day);
    m_deadline.setMonth(month);
    m_deadline.setYear(year);


}
std::string Task::getDeadline() const
{
    return m_deadline.Display();
}
void Task::setState(std::string state)
{
    m_state = state;
}
std::string Task::getState() const
{
    return m_state;
}

//PMS Def-n

PMS::PMS(std::ifstream &fin) {

    std::string token; // token to read strings from the file
    std::string project_line;
    std::string task_line;

    fin >> token;
    if (token.compare("project:") != 0) {
        std::cout << "\n-----File Data format is wrong !-----\n";
        exit(0);
    }

    while (!fin.eof()) {

        while (token.compare("task:") != 0) {
            project_line += token + " ";
            fin >> token;
        }

        Project project(project_line.substr(0, project_line.length() - 1));
        project_line = "";

        while (token.compare("project:") != 0 && token.compare("end") != 0) {

            task_line += token + " ";
            fin >> token;

            while (token.compare("task:") != 0 && token.compare("project:") != 0 && token.compare("end") != 0) {
                task_line += token + " ";
                fin >> token;
            }

            Task task(task_line);
            task_line = "";
            project.addTask(task);
        }
        m_projs.push_back(project);
    }
}

void PMS::add_new_project()
{
    std::cout << "Enter the name of the project: ";
    std::string token;
    std::getline(std::cin, token);
    Project proj;
    proj.setName(token);

    Task task;
    std::cout << "Enter the task's name: ";
    std::getline(std::cin, token);
    task.setName(token);

    std::cout << "Enter the assignee: ";
    std::getline(std::cin, token);
    task.setAssignee(token);

    std::cout << "Enter the state of the task: ";
    std::getline(std::cin, token);
    task.setState(token);

    std::cout << "Enter the deadline(day,month,year): ";
    int d,m,y;
    std::cin>>d>>m>>y;
    task.setDeadline(d,m,y);

    m_projs.push_back(proj);
    proj.addTask(task);

}


void PMS::add_new_task_to_the_project(){
    int index;
    std::cout << "\nType Project's index: ";
    std::cin >> index;

    if(index > m_projs.size() || index < 1){
        std::cout << "\nWrong Index !\n";
    }
    else{
        std::string token;
        Task task;

        std::cin.ignore();
        std::cout << std::endl << "Insert Task's name: ";
        std::getline(std::cin, token);
        task.setName(token);

        std::cout << std::endl << "Insert Task's status: ";
        std::getline(std::cin, token);
        task.setState(token);

        std::cout << std::endl << "Insert Task's assignee: ";
        std::getline(std::cin, token);
        task.setAssignee(token);

        std::cout << "\nInsert Task's deadline: ";
        int d,m,y;
        std::cin >> d >> m >> y;
        task.setDeadline(d,m,y);
        m_projs[index - 1].addTask(task);
    }
}
void PMS::add_projects_to_file(std::ostream &fout)
{
    std::string project_line = "";
    std::string task_line = "";
    for(int i = 0; i < m_projs.size(); ++i){
        fout << "project: " << m_projs[i].getName() << "\n";
        fout << m_projs[i].getTaskLine() << "\n";
    }
    fout << "end";
}

void PMS::edit_project(){
    int index;
    std::cout << "\nType Project's index: ";
    std::cin >> index;

    if(index > m_projs.size() || index < 1){
        std::cout << "\nWrong Index !\n";
    }
    else{
        std::string token;
        std::cin.ignore();
        std::cout << std::endl << "Type Project's name (write 'pass' if you don't want to change): ";
        std::getline(std::cin, token);
        if(token.compare("pass") == 0){
            return;
        }
        else{
            m_projs[index - 1].setName(token);
        }
    }
}

void PMS::edit_project_task(){
    int project_index;
    std::cout << "\nType Project's index: ";
    std::cin >> project_index;

    if(project_index > m_projs.size() || project_index < 1){
        std::cout << "\nWrong Index !\n";
    }
    else{
        int task_index;
        std::cout << "\nType Task's index: ";
        std::cin >> task_index;

        if(task_index > m_projs[project_index - 1].getTaskCount() || task_index < 1){
            std::cout << "\nWrong Index !\n";
        }
        else{
            m_projs[project_index - 1].setTask(task_index - 1);
        }
    }
}

void PMS::remove_project(){
    int index;
    std::cout << "\nType Project's index: ";
    std::cin >> index;

    if(index > m_projs.size() || index < 1){
        std::cout << "\nWrong Index !\n";
    }
    else{
        int i = 0;
        for(auto it = m_projs.begin(); it != m_projs.end(); ++it){
            if(i == index - 1){
                m_projs.erase(it);
                break;
            }
            ++i;
        }
    }
}

void PMS::remove_project_task(){
    int project_index;
    std::cout << "\nType Project's index: ";
    std::cin >> project_index;

    if(project_index > m_projs.size() || project_index < 1){
        std::cout << "\nWrong Index !\n";
    }
    else{
        int task_index;
        std::cout << "\nType Task's index: ";
        std::cin >> task_index;

        if(task_index > m_projs[project_index - 1].getTaskCount() || task_index < 1){
            std::cout << "\nWrong Index !\n";
        }
        else{
            m_projs[project_index - 1].removeTask(task_index - 1);
        }
    }
}

void PMS::show_projec_information(){
    int index;
    std::cout << "\nType Project's index: ";
    std::cin >> index;

    if(index > m_projs.size() || index < 1){
        std::cout << "\nWrong Index !\n";
    }
    else{
        m_projs[index - 1].showProject();
    }
}

void PMS::list_of_projects_and_tasks(){
    for(int i = 0; i < m_projs.size(); ++i){
        std::cout << "[" << i+1 << "]";
        m_projs[i].showProject();
    }
}





































