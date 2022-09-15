# Online session helper
#### Video Demo:  https://youtu.be/ABbqndwv7jY
#### Description:

### Introduction
    This is a web application which helps teachers to share and manage online session links with the student. Throughthe teacher can keep track which students have registered for the subject as well. The students have the ability toadd or remove subjects based on their choice. This web application is designed assuming that the teacher knows that the student will be following the lesson. My intention was to help my local community teachers who are facing dificulty in managing the zoom classes as well as for my personal zoom sessions.

### Reasons for undertaking this project:
    In the last two years the sudden switch to online education affected a lots of students in my village and community. During the pandemic we had a hard time communicating the zoom link as some would have recieved while and some would'nt. This created many problems. The lessons had to be delayed and in some case many were not able to join just because they did not recievethe link. Teachers ould create whatsapp groups to share the link. But this created many new problems such as privacy theft of students and piracies. And also teachers had to add or remove students and always maitain the group inorder to prevent any maliciousentries to the group. Thus I came to the conclusion of developing a free website where zoom links can be easily shared. Though this is not a completely built project, I am expecting to expand it and allow all hose whoar in need to make use of it.

### The mechanism of the website
    Initially the teacher has to register for teaching a certain subject.
    The teacher has to contact the admin (in this case me) in order to let the admin know if he/she is going o teach a new subject or and existing one. The admin of the websitewill check with the daabase and provide a secret code which the teacher can use to register.
    This safety mechanism prevent unknown people from registering as a teacher which could cause issues with the database.

    After the teacher registers his/her subject will be visible to the students in the add subjectsection. Note that if a teacher is not there for the subject the students can register and add the subject there about to learn.
    Thus when the teacher uploads the link the students will be able to join through the link by clicking the join button.
    The students also have the ability to remove subjectif they are no longer following it.

### Security
    I have developed many security precautions to prevent malicious inputs.
    All the passwords are hashed and unrecoveroble by the admin or anyother attacker.
    I also have applid a mechanism to prevent teachers or students to cross visit pages through URL manipulation
    A single username can be used only once to register.

### Expected updates
    I am expecting to upgrade this version such that teachers can teach multiple subjects and multiple teachers can teacha single subject
    Currently I have not implemented any mechanism to prevent students frommisusing the portal. But if needed the site can be equipped with a code which prevens students from accessing the zoom link without the code.

## Anygihub users are warmly welcome to update or edit the source code. But be sure to provide credit for thecreator 'fikrynuhuman183'