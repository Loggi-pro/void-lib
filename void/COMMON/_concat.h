#pragma once

#define __CONCAT_2(x, y) x ## y			//for internal use
#define __CONCAT_3(x, y,z) x ## y ## z	//for internal use
#define __CONCAT_4(x, y,z,d) x ## y ## z ## d 	//for internal use
#define __CONCAT_5(x, y,z,d,d2) x ## y ## z ## d ## d2 	//for internal use
#define CONCAT_2(x, y) __CONCAT_2(x, y) //Concat 2 define strings in one
#define CONCAT_3(x, y,z) __CONCAT_3(x, y,z) //Concat 3 define strings in one
#define CONCAT_4(x, y,z,d) __CONCAT_4(x, y,z,d) //Concat 4 define strings in one
#define CONCAT_5(x, y,z,d,d2) __CONCAT_5(x, y,z,d,d2) //Concat 5 define strings in one

#define _STRINGIFY(x) #x				//for internal use
#define TOSTRING(x) _STRINGIFY(x)		//convert define(x) in string ("")

#define ERROR_MSG(x) __FILE__"(" TOSTRING(__LINE__) ") : error: "#x //create error string in format:file(line):comment
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__) //variable- short filename
#define UNIQUE(x) CONCAT_2(x,__LINE__)