

// #include "../include/Interacoes.hpp"

// using namespace std;

// Interacoes::Interacoes(Ball &ball, Robot &robot) : ball(ball), robot(robot)
// {
//     // roboEstaComBola = false;
//     ballCoor = ball.getCoordinates();
//     robotCoor = robot.getCoordinates();
// }
// void Interacoes::setNewCoor()
// {
//     ballCoor = ball.getCoordinates();
//     robotCoor = robot.getCoordinates();
//     cout << "OiS " << ballCoor.x << ", " << ballCoor.y << endl;
// }
// bool Interacoes::itIsClose(double a, double b)
// {
//     cout << "OiI " << ballCoor.x << ", " << ballCoor.y << endl;
//     double distancia = a - b;
//     if ((distancia * distancia) <= 25)
//     {
//         return true;
//     }
//     return false;
// }
// void Interacoes::catchBall()
// {
//     cout << "OiC " << ballCoor.x << ", " << ballCoor.y << endl;
//     if (itIsClose(robotCoor.x, ballCoor.x) && itIsClose(robotCoor.y, ballCoor.y))
//     {
//         // roboEstaComBola = true;
//         cout << "Aqui\n";
//         ball.setCoordinates(robotCoor);
//     }
// }
// void Interacoes::interationRobotBall()
// {
//     // cout << "Bola: " << ballCoor.x << ", " << ballCoor.y << endl;
//     // cout << "Robo: " << robotCoor.x << ", " << robotCoor.y << endl;
//     // cout << "Bola: " << ball.getCoordinates().x << ", " << ball.getCoordinates().y << endl;
//     // cout << "Robo: " << robot.getCoordinates().x << ", " << robot.getCoordinates().y << endl;
//     setNewCoor();
//     catchBall();
// }
// void Interacoes::lancaBola() {}

// // bool itIsClose(double a, double b)
// // {
// //     double distancia = a - b;
// //     if ((distancia * distancia) <= 25)
// //     {
// //         return true;
// //     }
// //     return false;
// // }
// // if (itIsClose(robot1.getCoordinates().x, ball.getCoordinates().x) && itIsClose(robot1.getCoordinates().y, ball.getCoordinates().y))
// // {
// //     ball.setCoordinates(robot1.getCoordinates());
// // }