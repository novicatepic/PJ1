# C++ course-Project

This project involves the development of a platform for students, implemented as a console application.

Users of the system are required to have a username and password. They can enroll in multiple courses, where each course may have either student or teacher roles. Students can request to join a course, and their request must be approved by the respective teacher of that course. Users can establish friendships with other users by sending friend requests. When a user receives a friend request, they can either accept or decline it. Upon acceptance, the two users become friends. Messaging between users is only possible if they are friends. Students can also communicate with teachers, but only for courses in which they are enrolled. Message records are stored in the user's inbox.

The program's main flow can be summarized in four steps:

The application starts.
User A logs in with valid credentials, gaining access to the system.
User A sends a message to User B and then logs out.
User B logs in and checks the received message from User A.
Administrators of the system have the authority to add, modify, or remove courses and users. The system incorporates data persistence, ensuring that the system state is preserved even if the application is closed. Serialized data is loaded upon reopening the application, maintaining the previous state.

The application provides functionality to compare two courses, including finding the union, intersection, or difference between sets of students attending a specific course or those who have passed an exam. Additionally, users can filter messages in their inbox using specific search strings.

Please note that the last two paragraphs described in "PJ1 2021—22 Projektni zadatak.pdf" have not been implemented in this project.

The programming language used for this project is C++. Only the standard library and STL were utilized, and test data was integrated to facilitate testing. For the Serbian language specification, you can refer to "PJ1 2021—22 Projektni zadatak.pdf."
