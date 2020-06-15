#include <stdio.h>
#include <stdlib.h>
#include <string.h>		
#include <linux/input.h>	
#include <fcntl.h>
#include <dirent.h>		//directories
#include <unistd.h>		//open
#include <sys/ioctl.h>		//ioctl func
#include <stdint.h>
#include <sys/types.h>

/*NOTES:
 * maybe a tolower() function to be sure the "keyboard"-string will be identified everytime
 * maybe a setChar() function, possibly writing an own lib


*/

const char original_path[] = "/dev/input/event";

int get_eventcount();
int get_keyboardID(int);
char *analyze_keystroke(int);
char name[12];

int main(int argc, char **argv){

	int evcount, kbid, fd;
	evcount = get_eventcount();
	printf("Number of events(imo): %d\n", evcount);
	kbid = get_keyboardID(evcount);
	if(kbid < 0){
		printf("Unable to identify keyboard. I'm sorry :(\n");
		exit(1);
	}	
	printf("Keyboard has ID %d\n", kbid);
		
	char num[2];
	char path[sizeof(original_path) + 2];
	struct input_event ev;

	sprintf(num, "%d", kbid);
	memcpy(path, original_path, sizeof(original_path));
	strcat(path, num);
	fd = open(path, 'r');
	printf("Starting to capture %s\n", path);
	while(1){
		read(fd, &ev, sizeof(struct input_event));
		if((ev.type == 1) && (ev.value == 1 ))
			printf("%s pressed\n", analyze_keystroke(ev.code));
	}
}

int get_eventcount(){
	
	struct dirent *file;
	DIR * dirp;
	int evcount = 0;
	dirp = opendir("/dev/input");
	
	while((file = readdir(dirp)) != NULL){	
		if(file->d_type == DT_CHR){	
			if(strstr(file->d_name, "event") != NULL)
				evcount++;
		}
	}
	return evcount;
}

int get_keyboardID(int evcount){
	int i, fd;	
	char path[sizeof(original_path) + 2];
	char num[2];		//num will be converted to string
	char name[255];		//device name
	memcpy(path, original_path, sizeof(original_path));		
	for(i = 0; i < evcount; i++){
		sprintf(num, "%d", i);
		strcat(path, num);		
		fd = open(path, 'r');
		if(ioctl(fd, EVIOCGNAME(sizeof(name)), name) < 0)
			perror("IOCTL failure. Couldn't retrieve device name\n");
		if(strstr(name, "keyboard") != NULL){
			printf("Search found a keyboard. Name: %s\n", name);
			close(fd);
			return i;
		}
		close(fd);
		memcpy(path, original_path, sizeof(original_path));
	}
	return -1;
}

char *analyze_keystroke(int num){
	switch(num){
		case 1: memcpy(name, "esc", 4);
			break;
		case 2: memcpy(name, "1", 2);
			break;
		case 3: memcpy(name, "2", 2);
			break;
		case 4: memcpy(name, "3", 2);
			break;
		case 5: memcpy(name, "4", 2);
			break;
		case 6: memcpy(name, "5", 2);
			break;
		case 7: memcpy(name, "6", 2);
			break;
		case 8: memcpy(name, "7", 2);
			break;
		case 9: memcpy(name, "8", 2);
			break;
		case 10: memcpy(name, "9", 2);
			break;
		case 11: memcpy(name, "0", 2);
			break;
		case 12: memcpy(name, "-", 2);
			break;
		case 13: memcpy(name, "=", 2);
			break;
		case 14: memcpy(name, "backspace", 10);
			break;
		case 15: memcpy(name, "tab",43);
			break;
		case 16: memcpy(name, "q", 2);
			break;
		case 17: memcpy(name, "w", 2);
			break;
		case 18: memcpy(name, "e", 2);
			break;
		case 19: memcpy(name, "r", 2);
			break;
		case 20: memcpy(name, "t", 2);
			break;
		case 21: memcpy(name, "y", 2);
			break;
		case 22: memcpy(name, "u", 2);
			break;
		case 23: memcpy(name, "i", 2);
			break;
		case 24: memcpy(name, "o", 2);
			break;
		case 25: memcpy(name, "p", 2);
			break;
		case 26: memcpy(name, "(", 2);
			break;
		case 27: memcpy(name, ")", 2);
			break;
		case 28: memcpy(name, "enter", 6);
			break;
		case 29: memcpy(name, "leftctrl", 9);
			break;
		case 30: memcpy(name, "a", 2);
			break;
		case 31: memcpy(name, "s", 2);
			break;
		case 32: memcpy(name, "d", 2);
			break;
		case 33: memcpy(name, "f", 2);
			break;
		case 34: memcpy(name, "g", 2);
			break;
		case 35: memcpy(name, "h", 2);
			break;
		case 36: memcpy(name, "j", 2);
			break;
		case 37: memcpy(name, "k", 2);
			break;
		case 38: memcpy(name, "l", 2);
			break;
		case 39: memcpy(name, "l", 2);
			break;
		case 40: memcpy(name, ";", 2);
			break;
		case 41: memcpy(name, "grave", 6);
			break;
		case 42: memcpy(name, "leftshift", 10);
			break;
		case 43: memcpy(name, "\\", 2);
			break;
		case 44: memcpy(name, "z", 2);
			break;
		case 45: memcpy(name, "x", 2);
			break;
		case 46: memcpy(name, "c", 2);
			break;
		case 47: memcpy(name, "v", 2);
			break;
		case 48: memcpy(name, "b", 2);
			break;
		case 49: memcpy(name, "n", 2);
			break;
		case 50: memcpy(name, "m", 2);
			break;
		case 51: memcpy(name, ",", 2);
			break;
		case 52: memcpy(name, ".", 2);
			break;
		case 53: memcpy(name, "/", 2);
			break;
		case 54: memcpy(name, "rightshift", 11);
			break;
	
	
		case 56: memcpy(name, "leftalt", 9);
			break;
		case 57: memcpy(name, "space", 6);
			break;
		case 58: memcpy(name, "capslock", 9);
			break;
		case 59: memcpy(name, "F1", 3);
			break;
		case 60: memcpy(name, "F2", 3);
			break;
		case 61: memcpy(name, "F3", 3);
			break;
		case 62: memcpy(name, "F4", 3);
			break;
		case 63: memcpy(name, "F5", 3);
			break;
		case 64: memcpy(name, "F6", 3);
			break;
		case 65: memcpy(name, "F7", 3);
			break;
		case 66: memcpy(name, "F8", 3);
			break;
		case 67: memcpy(name, "F9", 3);
			break;
		case 68: memcpy(name, "F10",4);
			break;


		case 100: memcpy(name, "rightalt", 9);
			break;
		case 101: memcpy(name, "linefeed", 9);
			break;
		case 103: memcpy(name, "up", 3);
			break;
		case 104: memcpy(name, "pageup", 6);
			break;
		case 105: memcpy(name, "left", 5);
			break;
		case 106: memcpy(name, "right", 6);
		        break;
	
	
		case 108:
			  memcpy(name, "down", 5);
			  break;
		case 109:
			  memcpy(name, "pagedown", 9);
			  break;
		default: 
			  memcpy(name, "unknown", 8);
		}		
	return name;

	
}
