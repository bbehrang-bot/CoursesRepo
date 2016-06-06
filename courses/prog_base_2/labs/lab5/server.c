#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h> //  ptrdiff_t
#include <ctype.h>

#include "server.h"
#include "socket.h"
#include "Teacher.h"
#include "database.h"
#include "teacherFields.h"
#include "teacherListFields.h"
void server_API_investorByID(db_t * db, socket_t * client, http_request_t * req, int ID) {
	char strBuf[10240];
	// =====GET=====
	if (strcmp(req->method, "GET") == 0) {
		teacher_t * teacher = db_setNewTeacher(db, ID);
		char * teachJSON = teacher_toJSON(teacher);
		sprintf(strBuf,
			"HTTP/1.1 200 OK\n"
			"Content-Type: application/json\n"
			"Content-Length: %zu\n"
			"Connection: keep-alive\n"
			"\n%s", strlen(teachJSON), teachJSON);
		teacher_free(teacher);
		free(teachJSON);
	}
	// =====DELETE=====
	else if (strcmp(req->method, "DELETE") == 0) {
		// Getting the investor (and his info) before it was deleted
		teacher_t * delInvestor = db_setNewTeacher(db, ID);
		// If something went wrong
		if (delInvestor == NULL) {
			server_invalidResponce(client, "The investor was not deleted.");
			return;
		}
		// Deleting investor from database
		db_deleteTeacher(db, ID);

		char * delInvestorJSON = teacher_toJSON(delInvestor);
		// Printing info to console.
		printf("Deleted investor (%i-th one):\n%s\n", ID, delInvestorJSON);
		// Giving info to the client.
		char * delText = "Investor deleted successfully!";

		sprintf(strBuf,
			"HTTP/1.1 200 OK\n"
			"Content-Type: application/json\n"
			"Content-Length: %zu\n"
			"Connection: keep-alive\n"
			"\n%s", strlen(delText), delText);

		free(delInvestor);
		free(delInvestorJSON);
	}
	// =====Invalid command=====
	else {
		server_invalidResponce(client, "Invalid command.");
		return;
	}
	socket_write_string(client, strBuf);
	socket_close(client);
}
void server_API_homepage(socket_t * client, char * message) {
	char strBuf[10240];

	sprintf(strBuf,
		"HTTP/1.1 200 OK\n"
		"Content-Type: text/html\n"
		"Content-Length: %zu\n"
		"Connection: keep-alive\n"
		"\n%s", strlen(message), message);

	socket_write_string(client, strBuf);
	socket_close(client);
}
void server_API_allTeacher_WHERE(db_t * db, socket_t * client, http_request_t * req, int moneyInv, int moneyInvSign, int exp, int expSign) {

	char strBuf[10240];

	// =====GET=====
	if (strcmp(req->method, "GET") == 0) {
		teacherList_t * invWhereArr = database_getTeachArrFromDB_WHERE(db, moneyInv, moneyInvSign, exp, expSign);
		char * invArrJSON = teacher_arrToJSON(invWhereArr);
		sprintf(strBuf,
			"HTTP/1.1 200 OK\n"
			"Content-Type: application/json\n"
			"Content-Length: %zu\n"
			"Connection: keep-alive\n"
			"\n%s", strlen(invArrJSON), invArrJSON);
        puts(strBuf);
		free(invArrJSON);
		list_free(invWhereArr->tList);

	}
	// =====Invalid command=====
	else {
		server_invalidResponce(client, "Invalid command.");
		return;
	}

	socket_write_string(client, strBuf);
	socket_close(client);
}
void server_API_allTeacher(db_t * db, socket_t * clientSocket, http_request_t * req) {
	char strBuf[10240];

	// =====GET=====
	if (strcmp(req->method, "GET") == 0) {
		teacherList_t * tList = db_getAllTeachFromDB(db);
		char * invArrJSON = teacher_arrToJSON(tList);
		sprintf(strBuf,
			"HTTP/1.1 200 OK\n"
			"Content-Type: application/json\n"
			"Content-Length: %zu\n"
			"Connection: keep-alive\n"
			"\n%s", strlen(invArrJSON), invArrJSON);
		free(tList);
		free(invArrJSON);
	}
	// =====POST=====
	else if (strcmp(req->method, "POST") == 0) {
		// ID field is assigned automatically in database.
		// Every new info is briefly checked on validity.
		// If some field is not valid - the investor is not added.
		 teacher_t * teach = teacher_new();
		// Name field:

		char * str = http_request_getArg(req, "name");

		if (str != NULL && strlen(str) < 25) {
			strcpy(teach->name, str);
			puts(teach->name);
		}
		else {
			socket_write_string(clientSocket,"<body>name error<br>"
                                  "<a href=\"/teacher\">To teachers</a></body>");
			return;
		}
		// Nickname field:
		str = http_request_getArg(req, "salary");
		if (str != NULL && isdigit(str[0]) != 0 && strlen(str) < 7) {
			double p = atof(str);
			teach->salary = p;
		}
		else {
			socket_write_string(clientSocket,"<body>Salary error<br>"
                                  "<a href=\"/teacher\">To teachers</a></body>");
			return;
		}
		// Surname field:
		str = http_request_getArg(req, "experience");
		if (str != NULL && isdigit(str[0]) != 0 && strlen(str) < 7) {
			double p = atof(str);
			teach->experience = p;
		}
		else {
			socket_write_string(clientSocket,"<body>experience error<br>"
                                  "<a href=\"/teacher\">To teachers</a></body>");
			return;
		}
		// Rating field:

		// First investment (date struct) field:
		str = http_request_getArg(req, "hireDate");
		// Buffer for (str) string. First (str) will be checked on validity
		// and if everything is fine - the data will be copied again
		// and assigned to the fields.
		char buffForStr[30];
		strcpy(buffForStr, str);
		if (str != NULL) {
			// Checks if data of every field in date struct is valid:
			if (str[4] != NULL && str[4] == '-' && atoi(str) > 1900 && atoi(str) < 2016) {
				str = strtok(str, "-");
				str = strtok(NULL, "-");
				if (str != NULL && (atoi(str) >= 1 && atoi(str) <= 12)) {
					str = strtok(NULL, "-");
					if (str != NULL && (atoi(str) >= 1 && atoi(str) <= 31)) {
						// All data is valid:
						str = buffForStr;
						// Year:
						teach->hireDate.tm_year = atoi(str);
						// Month:
						str = strtok(str, "-");
						str = strtok(NULL, "-");
						teach->hireDate.tm_mon = atoi(str);
						// Day:
						str = strtok(NULL, "-");
						teach->hireDate.tm_mday = atoi(str);
					}
					else {
						socket_write_string(clientSocket,"<body>day error<br>"
                                  "<a href=\"/teacher\">To teachers</a></body>");
						return;
					}
				}
				else {
					socket_write_string(clientSocket,"<body>month error<br>"
                                  "<a href=\"/teacher\">To teachers</a></body>");
					return;
				}
			}
			else {
				socket_write_string(clientSocket,"<body>year error<br>"
                                  "<a href=\"/teacher\">To teachers</a></body>");
				return;
			}
		}
		// Adding investor to database
		db_addTeacher(db, teach);

		char * newInvestorJSON = teacher_toJSON(teach);
		// Printing info to console.
		printf("New investor created:\n%s\n", newInvestorJSON);
		// Giving info to the client.
		sprintf(strBuf,
			"HTTP/1.1 200 OK\n"
			"Content-Type: application/json\n"
			"Content-Length: %zu\n"
			"Connection: keep-alive\n"
			"\n%s", strlen(newInvestorJSON), newInvestorJSON);
		free(teach);
		free(newInvestorJSON);
	}
	// =====Invalid command=====
	else {
		server_invalidResponce(clientSocket, "Invalid command.");
		return;
	}

	socket_write_string(clientSocket, strBuf);
	socket_close(clientSocket);
}
char * teacher_parseAllToHTML(const teacherList_t * self) {
	char * buffHTML = calloc(10000, sizeof(char));
	char buffInvestor[1000];
	char buffURLInvestor[100];
	// constructing (opening) a 'carcass' for the HTML table (labels)
	sprintf(buffHTML,
		"<html><head></head><body><table border=\"1\">"
		"<tr><td>URL</td>"
		"<td>Name</td>"
		"<td>Salary</td>"
		"<td>experience</td>"
		"<td>hireDate</td>"
		"</tr>");

	// inserting all investors into this HTML table
	for (int i = 0; i < list_getSize(self->tList); i++) {
		teacher_t * teacher = list_get(self->tList, i);
		// link to the full description of investor
		sprintf(buffURLInvestor,
			"<a href=\"/teacher/%d\">Teacher #%d</a>",
			teacher->id, teacher->id);
		sprintf(buffInvestor,
			"<tr><td>%s</td>"
			"<td>%s</td>"
			"<td>%f</td>"
			"<td>%f</td>"
			"<td>%d-%d-%d</td>"
			"</tr>",
			buffURLInvestor, teacher->name, teacher->salary,
            teacher->experience, teacher->hireDate.tm_year,
            teacher->hireDate.tm_mday, teacher->hireDate.tm_mon);
            strcat(buffHTML, buffInvestor);
	}
	strcat(buffHTML, "</table></body></html>");

	return buffHTML;
}
char * teacher_parseToHTML(teacher_t * self)
{
   	char * buffHTML = calloc(10000, sizeof(char));
	// the simple HTML table with labels and one investor with full description inside
	sprintf(buffHTML,
		"<html><head></head><body><table border=\"1\">"
		"<tr><td>ID</td>"
		"<td>Name</td>"
		"<td>salary</td>"
		"<td>experience</td>"
		"<td>hire date</td>"
		"</tr>"
		"<tr><td>%d</td>"
		"<td>%s</td>"
		"<td>%f</td>"
		"<td>%f</td>"
		"<td>%d-%d-%d</td>"
		"</tr>"
		"</table></body></html>",
		self->id, self->name, self->salary,
		self->experience, self->hireDate.tm_year,
		self->hireDate.tm_mday, self->hireDate.tm_mon
		);

	return buffHTML;
}
void server_HTML_homepage(socket_t * client, char * message) {
	char strBuf[10240];

	char link[1024];
	strcpy(link, "<br/><a href=\"/teacher\">All teachers</a>");

	sprintf(strBuf,
		"HTTP/1.1 200 OK\n"
		"Content-Type: text/html\n"
		"Content-Length: %zu\n"
		"Connection: keep-alive\n"
		"\n%s%s", (strlen(message) + strlen(link)), message, link);
	socket_write_string(client, strBuf);
	socket_close(client);
}
void server_HTML_allTeachers(db_t * db, socket_t * client, http_request_t * req) {
    char strBuf[10240];

    // =====GET=====
    if (strcmp(req->method, "GET") == 0)
    {
        teacherList_t * tList = db_getAllTeachFromDB(db);
		char * line = teacher_parseAllToHTML(tList);

		char link[1024];
		strcpy(link, "<br/><a href=\"/new-teacher\">New-teacher</a>");

		sprintf(strBuf,
			"HTTP/1.1 200 OK\n"
			"Content-Type: text/html\n"
			"Content-Length: %zu\n"
			"Connection: keep-alive\n"
			"\n%s%s", (strlen(line) + strlen(link)), line, link);
		free(tList);
		free(line);
    }

	// =====POST=====
	else if (strcmp(req->method, "POST") == 0) {
		// ID field is assigned automatically in database.
		// Every new info is briefly checked on validity.
		// If some field is not valid - the investor is not added.
		teacher_t * teacher = teacher_new();
		// Name field:
		char * str = http_request_getArg(req, "name");
		if (str != NULL && strlen(str) < 25) {
			strcpy(teacher->name, str);
		}
		else {
			server_invalidResponce(client, "Invalid name.");
			return;
		}
		// Nickname field:

		// Rating field:
		str = http_request_getArg(req, "Experience");
		if (str != NULL && isdigit(str[0]) != 0 && strlen(str) < 7) {
			teacher->experience = atof(str);
		}
		else {
			server_invalidResponce(client, "Invalid experience.");
			return;
		}
		str = http_request_getArg(req, "salary");
		if (str != NULL && isdigit(str[0]) != 0 && strlen(str) < 7) {
			teacher->salary = atof(str);
		}
		else {
			server_invalidResponce(client, "Invalid experience.");
			return;
		}
		// First investment (date struct) field:
		str = http_request_getArg(req, "hireDate");
		// Buffer for (str) string. First (str) will be checked on validity
		// and if everything is fine - the data will be copied again
		// and assigned to the fields.
		char buffForStr[30];
		strcpy(buffForStr, str);
		if (str != NULL) {
			// Checks if data of every field in date struct is valid:
			if (str[4] != NULL && str[4] == '-' && atoi(str) > 1900 && atoi(str) < 2016) {
				str = strtok(str, "-");
				str = strtok(NULL, "-");
				if (str != NULL && (atoi(str) >= 1 && atoi(str) <= 12)) {
					str = strtok(NULL, "-");
					if (str != NULL && (atoi(str) >= 1 && atoi(str) <= 31)) {
						// All data is valid:
						str = buffForStr;
						// Year:
						teacher->hireDate.tm_year = atoi(str);
						// Month:
						str = strtok(str, "-");
						str = strtok(NULL, "-");
						teacher->hireDate.tm_mon = atoi(str);
						// Day:
						str = strtok(NULL, "-");
						teacher->hireDate.tm_mday = atoi(str);
					}
					else {
						server_invalidResponce(client, "Invalid day.");
						return;
					}
				}
				else {
					server_invalidResponce(client, "Invalid month.");
					return;
				}
			}
			else {
				server_invalidResponce(client, "Invalid year.");
				return;
			}
		}
		// Experience field:


		// Adding investor to our database
		db_addTeacher(db, teacher);

		char * teachHTML = teacher_parseToHTML(teacher);
		// Printing info to console.
		printf("New investor created:\n%s\n", teachHTML);
		// Giving info to the client.
		sprintf(strBuf,
			"HTTP/1.1 200 OK\n"
			"Content-Type: text/html\n"
			"Content-Length: %zu\n"
			"Connection: keep-alive\n"
			"\n%s", strlen(teachHTML), teachHTML);
		free(teachHTML);
		free(teacher);
	}

	// =====Invalid command=====
	else {
		server_invalidResponce(client, "Invalid command.");
		return;
	}

	socket_write_string(client, strBuf);
	socket_close(client);
}
void server_HTML_newTeacher(db_t * db, socket_t * client) {
	char strbuf[10240];
	char line[1000];
	// the HTML form to send post request
	strcpy(line, "<html><head></head><body><form action=\"http://127.0.0.1:5000/teacher\" method=\"POST\">"
		"Name:<br><input type=\"text\" name=\"name\" value='Ivan'><br>Experience:<br>"
		"<input type=\"text\" name=\"Experience\" value='25.5'><br>"
		"Salary:<br><input type=\"text\" name=\"salary\" value=\"200\"><br>"
		"hire Date:<br><input type=\"text\" name=\"hireDate\" value=\"1995-01-01\"><br>"
		"<input type=\"submit\" value='Send POST request' /></form></body></html>");

	sprintf(strbuf,
		"HTTP/1.1 200 OK\n"
		"Content-Type: text/html\n"
		"Content-Length: %zu\n"
		"Connection: keep-alive\n"
		"\n%s", strlen(line), line);

	socket_write_string(client, strbuf);
	socket_close(client);
}
void server_HTML_teacherByID(db_t * db, socket_t * client, http_request_t * req, int ID) {
	char strBuf[10240];

	// =====GET=====
	if (strcmp(req->method, "GET") == 0) {
		teacher_t * teacher = db_setNewTeacher(db, ID);
		char * line = teacher_parseToHTML(teacher);

		char link[1024];
		char linkURL[100];
		// the DELETE link with proper index
		sprintf(linkURL,
			"\"http://127.0.0.1:5000/teacher/%d\"",
			ID);

		// the main logic that the DELETE link consists of
		sprintf(link,
			"<br/><a href=\"#\" onclick=\"doDelete()\">Delete</a>"
			"<body><script>"
			"function doDelete() {"
			"var xhttp = new XMLHttpRequest();"
			"xhttp.open(\"DELETE\", %s, true);" // <-- %s (link) here -->
			"xhttp.send();}"
			"</script></body>",
			linkURL);// <-- link -->

		// info about the investor + delete link
		sprintf(strBuf,
			"HTTP/1.1 200 OK\n"
			"Content-Type: text/html\n"
			"Content-Length: %zu\n"
			"Connection: keep-alive\n"
			"\n%s%s", (strlen(line) + strlen(link)), line, link);
		free(teacher);
		free(line);
	}

	// =====DELETE=====
	else if (strcmp(req->method, "DELETE") == 0) {
		// Getting the investor (and his info) before it was deleted
		teacher_t * teacher = db_setNewTeacher(db, ID);
		// If something went wrong
		if (teacher == NULL) {
			server_invalidResponce(client, "The investor was not deleted.");
			return;
		}
		// Deleting the investor from database
		db_deleteTeacher(db, ID);

		char * delTeacherHTML = teacher_parseToHTML(teacher);
		// Printing info to console.
		printf("Deleted teacher (%i-th one):\n%s\n", ID, delTeacherHTML);
		// Giving info to the client.
		char * delText = "teacher deleted successfully!";

		sprintf(strBuf,
			"HTTP/1.1 200 OK\n"
			"Content-Type: text/html\n"
			"Content-Length: %zu\n"
			"Connection: keep-alive\n"
			"\n%s", strlen(delText), delText);

		free(delTeacherHTML);
		free(teacher);
	}

	// =====Invalid command=====
	else {
		server_invalidResponce(client, "Invalid command.");
		return;
	}

	socket_write_string(client, strBuf);
	socket_close(client);
}
void server_invalidResponce(socket_t * client, char * message) {
	char strBuf[1024];
	char * errText = message;

	sprintf(strBuf,
		"HTTP/1.1 404 \n"
		"Content-Type: text/html\n"
		"Content-Length: %zu\n"
		"\n%s", strlen(errText), errText);

	socket_write_string(client, strBuf);
	socket_close(client);
}
void server_analyzeRequest(http_request_t * request, socket_t * client, db_t * db) {

	// HTML: homepage
	if (strcmp(request->uri, "/") == 0) {
		server_HTML_homepage(client, "Hello. Pls, proceed further to list of investors (/teacher)"); // socket_close() function inside
	}

	// HTML: new-investor
	else if (strcmp(request->uri, "/new-teacher") == 0 || strcmp(request->uri, "/new-teacher/") == 0) {
		server_HTML_newTeacher(db, client); // socket_close() function inside
	}

	// HTML: all investors
	else if (strcmp(request->uri, "/teacher") == 0 || strcmp(request->uri, "/teacher/") == 0) {
		server_HTML_allTeachers(db, client, request); // socket_close() function inside
	}

	// HTML: single investor (by ID)
	// int that is working with the index of the investor
    else if (strstr(request->uri, "/teacher/") != NULL && strstr(request->uri, "/api/teacher/") == NULL) {
		// checking if index is proper (i.e. is a number)
		char * token = strtok(request->uri, "/");
		token = strtok(NULL, "/");
		if (token != NULL && isdigit(token[0]) != 0) {
			// checking if index presents among our investors
			int ID = atoi(token);
			if (db_isId(db, ID) == 1) {
				server_HTML_teacherByID(db, client, request, ID); // socket_close() function inside
			}
			// index does not present among our investors
			else {
				server_invalidResponce(client, "Invalid path."); // socket_close() function inside
			}
		}
		// index is not proper (i.e. is not a number)
		else {
			server_invalidResponce(client, "Invalid path."); // socket_close() function inside
		}
	}



	// API: homepage
	else if (strcmp(request->uri, "/api") == 0 || strcmp(request->uri, "/api/") == 0) {
		server_API_homepage(client, "Hello. Pls, proceed further to list of teacher (/api/teacher)"); // socket_close() function inside
	}

	// API: all investors
	else if (strcmp(request->uri, "/api/teacher") == 0 || strcmp(request->uri, "/api/teacher/") == 0) {
		server_API_allTeacher(db, client, request); // socket_close() function inside
	}
	// API: investors with int WHERE
	else if (strstr(request->uri, "/api/teacher/") == NULL && strstr(request->uri, "/api/teacher") != NULL) {
		int moneyInv;
		int expCondition;
		int exp;
		int dalaryCond;
		char * token = strtok(request->uri, "/=?&");
		token = strtok(NULL, "/=?&");
		if (token != NULL && strcmp(token, "teacher") == 0) {
			token = strtok(NULL, "/=?&");
			// Is 'key' correct?:
			if (token != NULL && (strcmp(token, "exp_gt") == 0 || strcmp(token, "exp_lt") == 0 || strcmp(token, "salary_gt") == 0 || strcmp(token, "salary_lt") == 0)) {
				// If first int is about moneyInv...
				if (strcmp(token, "exp_gt") == 0 || strcmp(token, "exp_lt") == 0) {
					if (strcmp(token, "exp_gt") == 0) {
						expCondition = 1;
					}
					else if (strcmp(token, "exp_lt") == 0) {
						expCondition = 0;
					}
					token = strtok(NULL, "/=?&");
					// Is 'value' correct?:
					if (token != NULL && isdigit(token[0]) != 0) {
						moneyInv = atoi(token);
						// ...Then second int must be about exp
						token = strtok(NULL, "/=?&");
						// Is 'key' correct?:
						if (token != NULL && (strcmp(token, "salary_gt") == 0 || strcmp(token, "salary_lt") == 0)) {
							if (strcmp(token, "salary_gt") == 0) {
								dalaryCond = 1;
							}
							else if (strcmp(token, "salary_lt") == 0) {
								dalaryCond = 0;
							}
							token = strtok(NULL, "/=?&");
							// Is 'value' correct?:
							if (token != NULL && isdigit(token[0]) != 0) {
								exp = atoi(token);
								server_API_allTeacher_WHERE(db, client, request, moneyInv, expCondition, exp, dalaryCond); // socket_close() function inside
							}
							else {
								server_invalidResponce(client, "Invalid path."); // socket_close() function inside
							}
						}
						else {
							server_invalidResponce(client, "Invalid path."); // socket_close() function inside
						}
					}
					else {
						server_invalidResponce(client, "Invalid path."); // socket_close() function inside
					}
				}
				// If first int is about exp...
				else if (strcmp(token, "salary_gt") == 0 || strcmp(token, "salary_lt") == 0) {
					if (strcmp(token, "salary_gt") == 0) {
						dalaryCond = 1;
					}
					else if (strcmp(token, "salary_lt") == 0) {
						dalaryCond = 0;
					}
					token = strtok(NULL, "/=?&");
					// Is 'value' correct?:
					if (token != NULL && isdigit(token[0]) != 0) {
						exp = atoi(token);
						// ...Then second int must be about moneyInv
						token = strtok(NULL, "/=?&");
						// Is 'key' correct?:
						if (token != NULL && (strcmp(token, "exp_gt") == 0 || strcmp(token, "exp_lt") == 0)) {
							if (strcmp(token, "exp_gt") == 0) {
								expCondition = 1;
							}
							else if (strcmp(token, "exp_lt") == 0) {
								expCondition = 0;
							}
							token = strtok(NULL, "/=?&");
							// Is 'value' correct?:
							if (token != NULL && isdigit(token[0]) != 0) {
								moneyInv = atoi(token);
								server_API_allTeacher_WHERE(db, client, request, moneyInv, expCondition, exp, dalaryCond); // socket_close() function inside
							}
							else {
								server_invalidResponce(client, "Invalid path."); // socket_close() function inside
							}
						}
						else {
							server_invalidResponce(client, "Invalid path."); // socket_close() function inside
						}
					}
					else {
						server_invalidResponce(client, "Invalid path."); // socket_close() function inside
					}
				}
			}
		}
		else {
			server_invalidResponce(client, "Invalid path."); // socket_close() function inside
		}
	}

	// API: single investor (by ID)
	// int that is working with the index of the investor
	else if (strstr(request->uri, "/api/teacher/") != NULL) {
		// checking if index is proper (i.e. is a number)
		char * token = strtok(request->uri, "/");
		token = strtok(NULL, "/");
		token = strtok(NULL, "/");
		if (token != NULL && isdigit(token[0]) != 0) {
			// checking if index presents among our investors
			int ID = atoi(token);
			if (db_isId(db, ID) == 1) {
				server_API_investorByID(db, client, request, ID); // socket_close() function inside
			}
			// index does not present among our investors
			else {
				server_invalidResponce(client, "Invalid path."); // socket_close() function inside
			}
		}
		// index is not proper (i.e. is not a number)
		else {
			server_invalidResponce(client, "Invalid path."); // socket_close() function inside
		}
	}
	// HTML/API: default
	// default invalid path
	else {
		server_invalidResponce(client, "Invalid path."); // socket_close() function inside
	}

}


// ========================================FUNCTIONS THAT ARE USED IF YOU USE THE API FORM========================================

//						Root page of the server
