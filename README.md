# PJ1-project

This project is about a platform for students and it is a console application.
User of the system has username and password and user can attend multiple courses. In each of the course user can be a student or a teacher. Student can send a request to attend a course which has to be accepted by teacher on that course. Each user can be a friend with any of the other users. To become a friend with other users, concrete user has to send them a friend request, and other user who received that request can either accept that request or decline it. If he accepted the request, than two users become friends. User can send message to other user in the system only if two of them are friends. Also, every student can chat with teachers, if the student is assigned to those courses. Messages are saved in the inbox of the user. The main idea of the program can be shown in four steps: 1) application starts, 2) user A enters credentials and is allowed to use the system if the credentials are valid, 3) user A sends a message to user B and logs out of the system, 4) user B signs in and checks a message that user A sent.

Administrator of the system can add, modify or remove courses and users. Data persistence is enabled in the system, so the state of the system is saved even if application closes. After opening the application, serialized data are loaded and data in the system is the same as it was before closing the application.

It is possible to compare two courses in the application: find union, intersection or difference between sets of students that attend a specific course, or students that passed an exam. Also, it is possible to filter messages in inbox. Filtering is done by using a specific string to search a message.

Last two paragraphs in PJ1 2021—22 Projekti zadatak.pdf are not implemented in this project.
Programming language used for this project is C++. Only standard library and STL were allowed in this project and test data was required so the application could be tested.
If you want to check out specification in Serbian language, read PJ1 2021—22 Projekti zadatak.pdf.
