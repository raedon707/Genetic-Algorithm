#include<iostream>
#include<string.h>
#include<stdlib.h>

#define pop_size 1000

using namespace std;

int i,j;
const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890.,/<>?';[]:=-(*&^%$#@!~)";

static char *rand_string(char *str, size_t size) {
	if(size) {
		--size;
		for(size_t n=0;n<size;n++) {
			int key = rand()%(int)(sizeof charset-1);
			str[n] = charset[key];
		}
		str[size] = '\0';
	}
	return str;
}

char* rand_string_alloc(size_t size) {
	char *s = (char*)malloc(size + 1);
	if(s) {
		rand_string(s,size);
	}
	return s;
}

//sorting population according to the fitness value of each species
void sort_pop(float fitness[], string population[]) {
	for(i=0;i<pop_size;i++) {
		for(j=0;j<pop_size;j++) {
			if(fitness[i]>fitness[j]){
				swap(fitness[i], fitness[j]);
				swap(population[i], population[j]);
			}
		}
	}
}

void fitness_function(string dest_string, string populations[], float fittest[]) {
	float fit_val = 0;
	for(i=0;i<pop_size;i++) {
		fit_val = 0;
		for(j=0;j<populations[i].length();j++) {
			if(populations[i][j] == dest_string[j]) {
				fit_val++;
			}
		}	
		fittest[i] = (fit_val/5)*100;
	}
	sort_pop(fittest, populations);
}

void crossover(string population[], string destination) {
	for(i = 0;i<pop_size; i=i+2){
		for(j = 0;j<population[i].length();j++) {
			if(j >= population[i].length()/2) {
				if(population[i][j] != destination[j])
					population[i][j] = population[i+1][j];
			}
			else {
				if(population[i+1][j] != destination[j])
					population[i+1][j] = population[i][j];
			}
		}
	}
}

void mutation(string population[]) {
	int mutation_number = 0;
	char *set;
	for(i = 0;i<pop_size; i++){
		mutation_number = rand()%(int)(6);
		int key = rand()%(int)(sizeof charset-1);
		set[0] = charset[key];
		set[1] = '\0';
		population[i][mutation_number] = set[0];
	}
}

int main() {
	string subjects[pop_size], a = "hello";
	int generation  = 0;
	float fitness[pop_size];
	
	//creating 1000 random population (strings for now)
	for(i=0;i<pop_size;i++) {
		subjects[i] = rand_string_alloc(6);
	}
	
	while(fitness[0] != 100) {
		generation++;
		fitness_function(a, subjects, fitness);
		crossover(subjects, a);
		//mutation(subjects);
		for(i=0;i<pop_size;i++) {
			cout<<subjects[i]<<" "<<fitness[i]<<endl;
			if(fitness[0] == 100) {
				system("pause");
				cout<<"String is found in "<<generation<<" generations"<<endl;
				break;
			}
		}
		
	}
}
