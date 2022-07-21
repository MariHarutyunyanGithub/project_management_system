
#include "prototype.hpp"
#include <iostream>

///////////////////մնաց թասկի edit-ն ու remove֊ը մշակեմ:

std::string date_to_string(Date date)/////////////////////////////////////////////ok
{
	std::string dedline = "";
	std::string day = std::to_string(date.m_day);
    std::string month = std::to_string(date.m_month);
    std::string year = std::to_string(date.m_year);
    dedline += (day + "/" + month + "/" + year);
    return dedline;
}

void project_steps()//////////////////////////////////////////////ok
{
	std::cout << std::endl << std::endl << "==========================" << std::endl;
	std::cout   << "[1]- create new project\n"  								
				<< "[2]- update project\n"				
				<< "[3]- remove project\n"				
				<< "[4]- search project\n"
                << "[5]- task functions\n"
				<< "[6]- exit from program\n"
				<< "==========================\n\n"
				<< "your choise: ___\b\b";
	short key;
	do{
		std::cin >> key;
		if (key < 1 || key > 6){
			std::cout << "your input is not correct, please, input an integer from [1;6].\n";
		}
	}while (key < 1 || key > 6);
	project_functions(key);
}

void project_functions(short key)//////////////////////////////////////////////ok
{
	switch(key){
			case 1: {project.create_project();}
				break;			
			case 2: {std::cout << "\nPlease, input the project name to update\n";
				std::string name;
				std::cin.ignore();
				std::getline(std::cin, name);
				project.edit_project(name);}
				break;
			case 3: {std::cout << "\nPlease, input the project name to delete\n";
				std::string name;
				std::cin.ignore();
				std::getline(std::cin, name);
				project.remove_project(name);}
				break;
			case 4: {
				std::string name;
				std::cout << "\nPlease, input the project name\n";
				std::cin.ignore();
				std::getline(std::cin, name); 
				project.search_project(name);}
				break;
            case 5: {task_steps();}
                break;
			case 6: {exit_from_program();}
				break;
			default :{std::cout << "\nyour input is not correct. Please, input numbers from diapazone [1;6]";
					project_steps();}	
			}
}

void Project::set_name(std::string name)/////////////////////////////////////ok
{
	file.close();
	file.open("projects.txt", std::ios::in | std::ios::out | std::ios::app);
	if(!file.is_open()){
		std::cout << "file is not opened,try again!\n";
		project_steps();
	}else{
		bool found{};
		std::string proj_name{};
		std::string text{};
		while(std::getline(file, text)){
			if (text[0] == 'P'){
				for (int i = 11; text[i] != '\0'; ++i){
					proj_name += text[i];
				}
				if (proj_name == name){
					found = true;
					std::cout << "The project with name '" << name 
						  << "' already exists!\n";
					file.close();
					project_steps();
				}
			}
			proj_name = {};
		}
		if (!found){
			project_name = name;
		}
		file.close();
	}
}

std::string Project::get_name() const
{
	return project_name;
}

void Project::set_deadline(Date date)
{
	m_deadline = date;
}

void Project::create_project()//////////////////////////////////////////////////ok
{
    file.open("projects.txt", std::ios::in | std::ios::out | std::ios::app);
	if(!file.is_open()){
        std::cout << "the file 'projects.txt' is not opened." << std::endl;
    }else{
		std::cout << "\nPlease, input the name of the new project:  ";
		std::string name;
		std::cin.ignore();
		std::getline(std::cin, name);
		set_name(name);
		file.open("projects.txt", std::ios::app);
		std::cout << "Please, input deadline.\nday:   ";
		int day;
		do{
			std::cin >> day;
			if (day <= 0 || day > 31){
				std::cout << "your input is not valid.please, input the correct date:   ";
			}
		}while (day <= 0 || day > 31);
		date.m_day = {day};
		std::cout << "month:   ";
		int month;
		do{
			std::cin >> month;
			if (month <= 0 || month > 12){
				std::cout << "your input is not valid. please, input correct month(an integer from diapazone [1;12]):   ";
			}
		}while (month <= 0 || month > 12);
		date.m_month = {month};
		int year;
		std::cout << "year:   ";
		do{
			std::cin >> year;
			if (year <= 2000 || year > 3000){
				std::cout << "your input is not valid. please, input correct year[2000;3000]:   ";
			}
		}while (year <= 2000 || year > 3000);
		date.m_year = {year};
		set_deadline(date);
		file << std::endl;
		file << "\nProject:   " << get_name() << std::endl
			 << "Deadline:  " << date_to_string(m_deadline) << std::endl;
		file.close();
		std::cout << "\nthe project with name \""<< name << "\" is created and saved successfuly!\n\n";	
	}
	project_steps();
}

void Project::edit_project(std::string name)////////////////////////////////////////////enteri xndira talis
{
	bool found{}; 
	file.open("projects.txt");
	if(!file.is_open()){
        std::cout << "the \"projects.txt\" file is not opened" << std::endl;
    }else{
		iofile.open("tmp.txt", std::ios::out | std::ios::app);
		if(!iofile.is_open()){
        	std::cout << "the 'tmp.txt' file is not opened" << std::endl;
    	}else{
			std::string text{};
			while (std::getline(file,text)){
				if (text[0] == 'P'){
					std::string proj_name{};
					for (int i = 11; text[i] != '\0'; ++i){
						proj_name += text[i];	
					}
					if (proj_name == name){
						found = true;
						char key;
						std::cout << "[n]- update project name" << std::endl
						          << "[d]- update deadline" << std::endl;
						do {
							std::cin >> key;
							if (key != 'n' && key != 'd'){
								std::cout << "your input is not correct, please, enter 'd' or 'n':    ";
							}
						}while (key != 'n' && key != 'd');
						if (key == 'n'){
							file.close();
							edit_project_name(name);
						}else{
							edit_deadline(name);
						}
					}
				}					
			}
			std::cout << "project \"" << name << "\" updated!!" << std::endl;	
			file.close();
			iofile.close();
			if(found){
				remove("projects.txt");
				rename("tmp.txt", "projects.txt");
			}			
		}	
		if (!found){
			std::cout << "In file 'projects.txt' not found the project with name '"<< name << "'!" << std::endl;
		}	
	}
	project_steps();
}

void Project::edit_project_name(std::string name)
{
	std::string new_name;
	bool found{};
	std::cout << "please, input the new name for project:    ";
	std::cin.ignore();
	std::getline(std::cin, new_name);
	project.set_name(new_name);
	file.open("projects.txt");
	if(!file.is_open()){
        std::cout << "the \"projects.txt\" file is not opened" << std::endl;
    }else{
		std::string text{};
		while (std::getline(file,text)){
			std::string proj_name = {};
			if (text[0] == 'P'){
				for (int i = 11; text[i] != '\0'; ++i){
					proj_name += text[i];		
				}				
				if (proj_name == name){
					found = true;
					text.erase(0, text.length());
					iofile << "Project:   " << new_name;
					std::getline(file, text);
					iofile << std::endl << text << std::endl;
				}else
					iofile << text << std::endl;
			}else if (text[0] == 'W'){
					std::string task_proj_name {};//for task's project name
					for (int i = 21; text[i] != '\0'; ++i){
						task_proj_name += text[i];
					}
					if (task_proj_name == name){
						text.erase(21, text.length());
						iofile << text + new_name;
						std::getline(file, text);
						iofile << std::endl << text;
						std::getline(file, text);
						iofile << std::endl << text;
						std::getline(file, text);
						iofile << std::endl << text;
						std::getline(file, text);
						text.erase(text.length() - name.length(), text.length());
						iofile <<std::endl << text << new_name << std::endl;
						std::getline(file, text);
						iofile << std::endl;
					}else
					iofile << text << std::endl;
			}else{
				iofile << text << std::endl;
			}
		}
	}
}

void edit_deadline(std::string name)
{
	std::string text{};
	// std::getline(file, text);
	iofile << std::endl << "Project:   " << name;
	std::getline(file, text);
	text.erase(0, text.length());
	std::cout << "Please, input the new deadline.\nday:   ";
	int day;
	do{
		std::cin >> day;
		if (day <= 0 || day > 31){
			std::cout << "your input is not valid.please, input the correct date:   ";
		}
	}while (day <= 0 || day > 31);
	iofile << "\nDeadline:  " << day << "/";
	std::cout << "month:   ";
	int month;
	do{
		std::cin >> month;
		if (month <= 0 || month > 12){
			std::cout << "your input is not valid. please, input correct month(an integer from diapazone [1;12]):   ";
		}
	}while (month <= 0 || month > 12);
	iofile << month << "/";
	int year;
	std::cout << "year:   ";
	do{
		std::cin >> year;
		if (year <= 2000 || year > 3000){
			std::cout << "your input is not valid. please, input correct year [2000;3000]:   ";
		}
	}while (year <= 2000 || year > 3000);
	iofile << year;
	std::cout << "project's deadline updated!" << std::endl << std::endl;
	remove("projects.txt");
	rename("tmp.txt", "projects.txt");
	project_steps();
}

void Project::search_project(std::string name)///////////////////////////////////////////////ok
{
	bool found{};
	std::string text {};//ֆայլի ինֆորմացիան տող առ տող պահելու համար
	std::string proj_name {};//պրոյեկտի անունը պահելու համար
	std::string task_proj_name {};//task֊ի պրոյեկտի անունը պահելու համար
	std::string proj_task{}; //task֊ի տվյալները պահելու համար
	file.open("projects.txt");
	if(!file.is_open()){
        std::cout << "the \"projects.txt\" file is not opened" << std::endl;
    }else{
		while (std::getline(file,text)){
			if (text[0] == 'P'){
				for (int i = 11; text[i] != '\0'; ++i){
					proj_name += text[i];		
				}
			}
			if (proj_name == name){
				found = true;
				std::cout << "\nProject name: " << proj_name << std::endl;
				std::getline(file, text);
				std::cout <<  text << std::endl; 
				std::cout << std::endl << "   project's tasks\n" << std::endl;
			}
				proj_name = "";
		}
		if (!found){
			std::cout << "Not found" << std::endl;
		}
		file.close();
		file.open("projects.txt");
		if(!file.is_open()){
        std::cout << "the \"projects.txt\" file is not opened" << std::endl;
    	}else{
			while (std::getline(file,text)){
				if (text[0] == 'W'){
					for (int i = 21; text[i] != '\0'; ++i){
						task_proj_name += text[i];
					}
				}
				if (task_proj_name == name){
						std::getline(file, text);
						proj_task += text;
						proj_task += "\n";
						std::getline(file, text);
						proj_task += text;
						proj_task += "\n";
						std::getline(file, text);
						proj_task += text;
						proj_task += "\n";
						std::getline(file, text);
						proj_task += text;
						proj_task += "\n\n";
					}
				task_proj_name = "";
			}
			std::cout << proj_task;
			std::cout << std::endl;
			file.close();		
		}
	}
	project_steps();
}

void Project::remove_project(std::string name)///////////// ooookkkkkk!!!!!!!!!!!!!
{
	bool found{};
	std::string text {};//to store file information line by line
	
	file.open("projects.txt");//original file
	if(!file.is_open()){
        std::cout << "the \"projects.txt\" file is not opened" << std::endl;
    }else{
		iofile.open("tmp.txt", std::ios::out | std::ios::app);//reserve file
		if (!iofile.is_open()){
			std::cout << "the 'tmp.txt' file is not opened!";
		}else{
			while (std::getline(file,text)){
				std::string proj_name = {};
				if (text[0] == 'P'){
					for (int i = 11; text[i] != '\0'; ++i){
						proj_name += text[i];		
					}				
					if (proj_name == name){
						found = true;
						text.erase(0, text.length());
						std::getline(file, text);
						text.erase(0, text.length());
					}
				}
				if (text[0] == 'W'){
					std::string task_proj_name {};//for task's project name
					for (int i = 21; text[i] != '\0'; ++i){
						task_proj_name += text[i];
					}				
					if (task_proj_name == name){
						text.erase(0, text.length());
						std::getline(file, text);
						text.erase(0, text.length());
						std::getline(file, text);
						text.erase(0, text.length());
						std::getline(file, text);
						text.erase(0, text.length());
						std::getline(file, text);
						text.erase(0, text.length());
					}
				}				
				iofile << text;
				iofile << std::endl;
			}
			iofile.close();
		}
		file.close();
		if (!found){
			std::cout << "Not found" << std::endl;
		}else {
			std::cout << "project \"" << name << "\" deleted!!" << std::endl;
		}
	}
	remove("projects.txt");
	rename("tmp.txt", "projects.txt");
	project_steps();
}

////////////////////////////////////       task         /////////////////////////////////////

void task_steps()
{
    std::cout << std::endl << "=========================" << std::endl;
    std::cout 	<< "[1]- create new task for project\n"
				<< "[2]- update task\n"
				<< "[3]- remove task\n"
				<< "[4]- search task\n"
				<< "[5]- go to main menu.\n"
				<< "[6]- exit from program\n"
				<<"=============================\n\n"
				<< "your choise: ___\b\b";
	short key;
	do{
		std::cin >> key;
		if (key < 1 || key > 7){
			std::cout << "your input is not correct, please, input an integer from [1;6].\n";
		}
	}while (key < 1 || key > 7);
	task_functions(key);
}

void task_functions(short key)
{
	switch(key){
		case 1: {task.create_task();}
			break;			
		case 2: {std::cout << "\nPlease, input the task name to update\n";
			std::string name;
			std::cin.ignore();
			std::getline(std::cin, name);
			task.edit_task(name);}
				break;
			case 3: {std::cout << "\nPlease, input the task name to delete\n";
				std::string name;
				std::cin.ignore();
				std::getline(std::cin,name);
				task.remove_task(name);}
				break;
			case 4: {
				std::string name;
				std::cout << "\nPlease, input the task name\n";
				std::cin.ignore();
				std::getline(std::cin, name);
				task.search_task(name);}
				break;
			case 5: {project_steps();}
				break;
			case 6: {exit_from_program();}
				break;
			default :{std::cout << "\nyour input is not correct. Please, input numbers from diapazone [1;7]";
					project_steps();}	
			
	}
}

void Task::set_name(std::string name)
{
	task_name = name;
}

std::string Task::get_name() const
{
	return task_name;
}

void Task::set_proj_name(std::string proj_name)
{ 
	file.close();
	bool found{};
	file.open("projects.txt");
	if(!file.is_open()){
        std::cout << "the \"projects.txt\" file is not opened" << std::endl;
    }else{
        std::string text = {};
		std::string name = "";
		while (std::getline(file, text)){ 
			if (text[0] == 'P'){
				for (int i = 11; text[i] != '\0'; ++i){
					name += text[i];
				}		
				if (name == proj_name){
					found = true;
					project_name = proj_name;
				}
			}
			name = "";
		}
		if (!found){
			std::cout << "Project with name '" << proj_name << "' is not found!" << std::endl;
			task_steps(); 
		}
	}
}

std::string Task::get_proj_name()const
{
	return project_name;
}

void Task::set_deadline(Date date)
{
	m_deadline = date;
}

void Task::set_assignee_name(std::string name)
{
	assignee_name = name;
}

std::string Task::get_assignee_name()
{
	return assignee_name;
}

void Task::create_task()
{
	std::cout << "Please, input the name of the task:  ";
	std::string name;
	std::cin.ignore();
	std::getline(std::cin, name);
	task.set_name(name);
	std::cout << "which project's task is? enter the project name:     ";
	std::string proj_name;
	std::getline(std::cin, proj_name);
	task.set_proj_name(proj_name);
	std::cout << "input dedline.\ndate:   ";
	int day;
	do{
		std::cin >> day;
		if (day <= 0 || day > 31){
			std::cout << "your input is not valid.please, input the correct date  [1;31]:   ";
		}
	}while (day <= 0 || day > 31);
	date.m_day = {day};
	std::cout << "month:   ";
	int month;
	do{
		std::cin >> month;
		if (month <= 0 || month > 12){
			std::cout << "your input is not valid. please, input correct month(an integer from diapazone [1;12]):   ";
		}
	}while (month <= 0 || month > 12);
	date.m_month = {month};
	int year;
	std::cout << "year:   ";
	do{
		std::cin >> year;
		if (year < 2000 || year > 3000){
			std::cout << "your input is not valid. please, input correct year [2000;3000]:   ";
		}
	}while (year <= 2000 || year > 3000);
	date.m_year = {year};
	set_deadline(date);
	std::cout << "input the assignee name\n";
	std::string ass_name;
	std::cin.ignore();
	std::getline(std::cin,ass_name);
	set_assignee_name(ass_name);
	set_state();		
	std::cout << "the task is created successfuly!\n\n";
	file.open("projects.txt", std::ios::out | std::ios::app);
	if(file.is_open()){
		file << std::endl << std::endl;
		file << "Which_poject's task: " << get_proj_name() << std::endl
		 	 << "Task:                " << get_name() << std::endl
		 	 << "dedline:             " << date_to_string (m_deadline) << std::endl
		 	 << "Assignee:            " << get_assignee_name() << std::endl
	     	 << "State:               " << get_state() << ":  in project:  " << get_proj_name() << std::endl << std::endl;
				
	} 				
	file.close();
	std::cout << "task has been saved." << std::endl;
	task_steps();
}

void Task::set_state()///////////////////////////////////ok
{
	std::string new_state;
	std::cout << "set status(to do/ in progress/ done):    ";
	std::cin.ignore();
	std::getline(std::cin, new_state);
	if (new_state != "in progress" && new_state != "done"){
		task.state = "to do";
	}
	else{
		task.state = new_state;
	}
	file.close();
}

std::string Task::get_state()const///////////////////////ok
{
	return task.state;
}

void Task::edit_task(std::string name)
{
	task.remove_task(name);
	create_task();		
	std::cout << "task uptated!\n" << std::endl;
	bool found = true;
			
	if (!found){
		std::cout << "Not found the task!" << std::endl;
		file.close();
		return;
	}
	file.close();
}

void Task::search_task(std::string name)/////////////////////////////////////////////////////ok
{
	std::string text {};
	std::string task_name {};
	file.open("projects.txt");
	while (std::getline(file,text)){
		if (text[0] == 'T'){
			for (int i = 21; text[i] != '\0'; ++i){
				task_name += text[i];		
			}
			if (task_name == name){
				std::cout << std::endl << std::endl << "Task name:           " 
				<< task_name << std::endl;
				std::getline(file, text);
				std::cout <<  text << std::endl;
				std::getline(file, text);
				std::cout <<  text << std::endl;
				std::getline(file, text);
				std::cout <<  text << std::endl;
				file.close(); 
				task_steps();
				return;
			}
		task_name = {};
		}
	}
	std::cout << "Not found" << std::endl;
	file.close();
	task_steps();
}

void Task::remove_task(std::string name)
{
	file.open("projects.txt");
	if(!file.is_open()){
        std::cout << "the \"projects.txt\" file is not opened" << std::endl;
    }else{
        std::string text;
		std::string task_name{};
		std::string proj_string{};
		std::fstream iofile;
		iofile.open("tmp.txt", std::ios::out);
		if (!iofile.is_open()){
			std::cout << "the file 'tmp.txt' is not opened, try again!";
			task_steps();
		}else{
			while (std::getline(file,text)){
				if (text[0] == 'W'){
					for (int i{}; text[i] != '\0'; ++i){
						proj_string += text[i];
					}
					text.erase(0, text.length());
					//text = "";
					std::getline(file, text);
					for (int i = 21; text[i] != '\0'; ++i){
						task_name += text[i];		
					}
					if (task_name == name){
						text.erase(0, text.length());
						std::getline(file, text);
						text.erase(0, text.length());
						std::getline(file, text);
						text.erase(0, text.length());
						std::getline(file, text);
						text.erase(0, text.length());
						goto label;
					}else{
						text.erase(0, text.length());
						iofile << proj_string << std::endl;
						iofile << "Task:               " << task_name << std::endl;
					}
				}
				iofile << text;
				iofile << '\n';
				label:
				task_name = {};
			}
			file.close();
			iofile.close();
			remove("projects.txt");
			rename("tmp.txt", "projects.txt");
			std::cout << "task \"" << name << "\" deleted!!" << std::endl;
		}
	}
}

void exit_from_program()///////////////////////////////////////////////////////////////////ok
{
	std::cout << "are you sure, you really want to exit from program?(y / n) \n";
	std::string key;
	do {
		std::cin >> key;	
		if (key != "y" && key != "n"){
			std::cout << "your input is not correct. Please, input 'y' or 'n'\n";	
		}
	}while(key != "y" && key != "n");				
		if(key == "y"){
			std::cout << "\n\n===========  BYE  ==========\n\n";
			exit(0);
		}else if(key == "n"){
			project_steps();					
		}
}

int main(){
	std::cout << "\nWellcome to PROJECT MANAGEMENT SYSTEM";
	project_steps();
	return 0;
}
