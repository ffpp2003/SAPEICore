#include <iostream>
#include <vector>
#include "Client.h"
#include "DataBase.h"
#include "Vehicle.h"
//
//using namespace std;
//
//DataBase baseDeDatos;
//
//Client cliente1(1234, "Ignacio", 18, "El Prado", "grmngl90@gmail.com", "3516277576" ,"OXN 071", "Auto Comun", "Rojo", "Gol", "2015");
//
//int main(){
//  DataBase db("SAPEI.db");
//  Vehicle vehiculo("AG 191 XK","Chata","Negro","Ford","2024");
//  cliente1.addVehicle(vehiculo);
//
//  return 0;
//}

#include <cstdint>
#include <iostream>

using namespace std;

int main() {
    Client c1(0, "Juan Perez", 30, "Calle Falsa 123", "juan@example.com", "123456789", "ABC123", "Sedan", "Rojo", "Toyota", "Corolla");
    Client c2(25, "Maria Gomez", 28, "Avenida Siempre Viva 742", "maria@example.com", "987654321", "XYZ456", "SUV", "Azul", "Ford", "Escape");
    Client c3(5, "Pedro Martinez", 40, "Calle Larga 789", "pedro@example.com", "321321321", "GHI112", "Convertible", "Amarillo", "Mazda", "MX-5");
    Client c4(6, "Lucia Sanchez", 27, "Calle Cortada 654", "lucia@example.com", "654654654", "JKL131", "Sedan", "Blanco", "Nissan", "Altima");
    Client c5(7, "Javier Lopez", 32, "Calle del Sol 852", "javier@example.com", "789789789", "MNO145", "Coupe", "Gris", "Honda", "Civic");
    Client c6(8, "Sofia Martinez", 29, "Avenida del Mar 963", "sofia@example.com", "321987321", "PQR159", "Pickup", "Café", "Toyota", "Tacoma");
    Client c7(9, "Diego Fernandez", 45, "Calle de la Amistad 159", "diego@example.com", "852369741", "STU168", "SUV", "Negro", "Hyundai", "Tucson");
    Client c8(10, "Valentina Salas", 26, "Calle de los Sueños 258", "valentina@example.com", "753951852", "VWX174", "Hatchback", "Rojo", "Kia", "Forte");

    c1.addVehicle(Vehicle("LMN789", "Camioneta", "Negro", "Chevrolet", "S10"));
    c1.addVehicle(Vehicle("DEF101", "Hatchback", "Verde", "Volkswagen", "Polo"));

    DataBase db("SAPEI.db");

    db.addClient(c1);
    db.addClient(c2);
    db.addClient(c3);
    db.addClient(c4);
    db.addClient(c5);
    db.addClient(c6);
    db.addClient(c7);
    db.addClient(c8);


    //cout << db.getClientById(0) << endl;
    cout << db.getClientByName("Juan Perez") << endl;

    db.showClients();

    return 0;
}
