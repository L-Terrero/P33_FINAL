#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <vector>
#include <functional>
#include <filesystem>
#include <cmath>
#include "P33_FUNC.h"

using namespace std;
namespace fs = filesystem;

const string CREDENCIALES_FILEPATH = "C:\\Users\\luist\\CLionProjects\\untitled6\\credencialesP33.txt";
const string CLASSES_FILEPATH = "C:\\Users\\luist\\CLionProjects\\untitled6\\classes.txt";

void RevisionYGuardadoDeClases() {
    if (!fs::exists(CREDENCIALES_FILEPATH)) {
        ofstream file(CREDENCIALES_FILEPATH);
        if (!file) {
            cout << "Error al crear el archivo de usuarios.\n";
            return;
        }
        cout << "Archivo de usuarios creado exitosamente.\n";
    }
}

vector<string> CargarClases() {
    vector<string> classes;
    ifstream file(CLASSES_FILEPATH);
    if (!file) {
        cout << "Error al cargar las clases. Asegurese de que 'classes.txt' exista.\n";
        return classes;
    }

    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            classes.push_back(line);
        }
    }
    return classes;
}

void GuardarClases(const vector<string>& classes) {
    ofstream file(CLASSES_FILEPATH);
    if (!file) {
        cout << "Error al guardar las clases.\n";
        return;
    }

    for (const auto& cls : classes) {
        file << cls << endl;
    }
}

void hora() {
    time_t time1;
    time(&time1);
    cout << ctime(&time1);
}

void RegistrarUsuario() {
    string username, password;
    cout << "Ingrese un nombre de usuario: ";
    cin >> username;
    cout << "Ingrese una contrasena: ";
    cin >> password;

    ofstream file(CREDENCIALES_FILEPATH, ios::app);
    if (!file) {
        cout << "Error al abrir el archivo para guardar el usuario.\n";
        return;
    }
    file << username << " " << password << endl;
    cout << "Usuario registrado exitosamente.\n";
}

bool IniciarSesion() {
    string username, password;
    cout << "Ingrese su nombre de usuario: ";
    cin >> username;
    cout << "Ingrese su contrasena: ";
    cin >> password;

    ifstream file(CREDENCIALES_FILEPATH);
    if (!file) {
        cout << "Error al abrir el archivo de usuarios.\n";
        return false;
    }

    string storedUsername, storedPassword;
    bool found = false;

    while (file >> storedUsername >> storedPassword) {
        if (storedUsername == username && storedPassword == password) {
            cout << "Inicio de sesion exitoso.\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Usuario o contrasena incorrectos.\n";
        return false;
    }

    return true;
}

void CambiarNombreDeClase(vector<string>& classes) {
    int index;
    string newName;

    cout << "Ingrese el numero de la clase que desea cambiar (1-" << classes.size() << "): ";
    if (!(cin >> index)) {
        cout << "Entrada invalida. Debe ser un numero." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    if (index < 1 || index > classes.size()) {
        cout << "Numero de clase invalido!" << endl;
        return;
    }

    cin.ignore();
    cout << "Ingrese el nuevo nombre para la clase " << classes[index - 1] << ": ";
    getline(cin, newName);

    classes[index - 1] = newName;
    cout << "Nombre de clase actualizado correctamente." << endl;

    GuardarClases(classes);
}

void AgregarClase(vector<string>& classes) {
    string newClass;
    char decision;

    do {
        cout << "Ingrese el nombre de la nueva clase: ";
        cin.ignore();
        getline(cin, newClass);

        classes.push_back(newClass);
        GuardarClases(classes);
        cout << "Clase agregada exitosamente: " << newClass << endl;

        bool validInput = false;
        while (!validInput) {
            cout << "Desea agregar otra clase? (Y/N): ";
            cin >> decision;
            decision = tolower(decision);

            if (decision == 'y' || decision == 'n') {
                validInput = true;
                if (decision == 'n') {
                    cout << "Volviendo al menu principal.\n";
                }
            } else {
                cout << "Ingrese tan solo 'Y' o 'N'.\n";
            }
        }
    } while (decision == 'y');
}


void EliminarClase(vector<string>& classes) {
    int index;

    cout << "Lista de clases:\n";
    for (int i = 0; i < classes.size(); ++i) {
        cout << i + 1 << ") " << classes[i] << endl;
    }

    cout << "Ingrese el numero de la clase que desea eliminar: ";
    if (!(cin >> index) || index < 1 || index > classes.size()) {
        cout << "Numero de clase invalido.\n";
        return;
    }

    string removedClass = classes[index - 1];
    classes.erase(classes.begin() + index - 1);

    GuardarClases(classes);

    cout << "Clase eliminada exitosamente: " << removedClass << endl;
}

void MostrarClases(const vector<string>& classes) {
    cout << "Lista de clases:\n";
    for (int i = 0; i < classes.size(); ++i) {
        cout << i + 1 << ") " << classes[i] << endl;
    }
}

void Asistencia() {
    int ClasesTotal;
    int ClasesAusente;

    do {
    cout << "Cuantas clases ha tomado? \n";
    cin >>  ClasesTotal;
    }
    while (ClasesTotal < 0);

    do {
        cout << "Ha faltado a : \n";
        cin >> ClasesAusente;
    }
    while (ClasesAusente > ClasesTotal || ClasesAusente < 0);

    int Total = ClasesTotal - ClasesAusente;
    cout << "Ha asistido a un total de: " << Total << " clases de " << ClasesTotal << " clases\n";

    double porciento = (static_cast<double>(Total) / ClasesTotal) * 100;
    cout << "En promedio, asiste a un total de: " << porciento << "%\n";
}

void Promedio(const vector<string>& classes) {
    if (classes.empty()) {
        cout << "No hay clases registradas. Por favor, agregue clases primero.\n";
        return;
    }

    vector<double> notas(classes.size(), 0);
    int NotaMaxima;

    do {
    cout << "Ingrese la nota maxima en su institucion \n";
    cin >> NotaMaxima ; } while (NotaMaxima <= 0);

    cout << "Ingrese sus calificaciones:\n";

    for (size_t i = 0; i < classes.size(); ++i) {
        do {
            cout << classes[i] << ": ";
            cin >> notas[i];

            if (notas[i] < 0 || notas[i] > NotaMaxima) {
                cout << "Calificacion invalida. Ingrese un valor entre 0 y " << NotaMaxima << ":" << endl;
            }
        } while (notas[i] < 0 || notas[i] > NotaMaxima);
    }

    double NotaPromedio = 0;
    for (const double grade : notas) {
        NotaPromedio += grade;
    }
    NotaPromedio /= notas.size();

    cout << "Promedio: " << NotaPromedio << endl;

}

void HoraHastaSalida() {
    time_t now;
    struct tm Hora_Salida = {};

    time(&now);
    struct tm* Hora_Actual = localtime(&now);

    int HoraElegida;
    int MinutosElegidos;

    do {
        cout << "Ingrese su hora de salida: ";
        cin >> HoraElegida;
    } while (HoraElegida > 24 || HoraElegida < 0);

    do {
        cout << "Ingrese su minuto de salida: ";
        cin >> MinutosElegidos;
    } while (MinutosElegidos > 60 || MinutosElegidos < 0);


    Hora_Salida = *Hora_Actual;
    Hora_Salida.tm_hour = HoraElegida;
    Hora_Salida.tm_min = MinutosElegidos;
    Hora_Salida.tm_sec = 0;

    time_t Hora_Salida1 = mktime(&Hora_Salida);

    if (difftime(Hora_Salida1, now) < 0) {
        Hora_Salida.tm_mday += 1;
        Hora_Salida1 = mktime(&Hora_Salida);
    }

    int seconds_left = difftime(Hora_Salida1, now);
    int hours_left = seconds_left / 3600;
    int minutes_left = (seconds_left - hours_left * 3600) / 60;
    int seconds_left_int = seconds_left - (hours_left * 3600 + minutes_left * 60);

    cout << "Tiempo restante hasta su hora de salida: "
         << hours_left << " horas, "
         << minutes_left << " minutos, "
         << seconds_left_int << " segundos.\n";
}


void EliminarUsuario() {
    string usernameToDelete;
    string PasswordSec;
    cout << "Ingrese el nombre de usuario a eliminar: ";
    cin >> usernameToDelete;

    cout << "Ingrese la clave: ";
    cin >> PasswordSec;

    ifstream inputFile(CREDENCIALES_FILEPATH);
    if (!inputFile) {
        cout << "Error al abrir el archivo de usuarios.\n";
        return;
    }

    vector<string> lines;
    string username, password;
    bool found = false;
    bool passwordCorrect = false;

    while (inputFile >> username >> password) {
        if (username == usernameToDelete) {
            found = true;
            if (password == PasswordSec) {
                passwordCorrect = true;
            }
        }
        if (username != usernameToDelete) {
            lines.push_back(username + " " + password);
        }
    }
    inputFile.close();

    if (!found) {
        cout << "Usuario no encontrado.\n";
        return;
    }

    if (!passwordCorrect) {
        cout << "No se pudo probar propiedad del usuario. No se puede eliminar el usuario.\n";
        return;
    }

    ofstream outputFile(CREDENCIALES_FILEPATH, ios::trunc);
    if (!outputFile) {
        cout << "Error al abrir el archivo para escritura.\n";
        return;
    }

    for (const string& line : lines) {
        outputFile << line << endl;
    }

    cout << "Usuario eliminado exitosamente.\n";
}

bool SwitchReset() {
    char choice;
    while (true) {
        cout << "\nDesea volver al menu principal? (Y/N): ";
        cin >> choice;
        if (choice == 'Y' || choice == 'y') {
            return true;
        } else if (choice == 'N' || choice == 'n') {
            return false;
        } else {
            cout << "Entrada invalida. Por favor, ingrese 'Y' o 'N'.\n";
        }
    }
}

int main() {
    vector<string> classes = CargarClases();

    int opcion;
    bool opc = false;
    bool loggedIn = false;
    bool salir = false;

    RevisionYGuardadoDeClases();

    cout << "Fecha y hora actual: ";
    hora();

    do {
        while (!loggedIn) {
            cout << "\nElija una opcion:\n";
            cout << "1) Iniciar sesion\n";
            cout << "2) Registrar usuario\n";
            cout << "0) Salir\n";
            cout << "Opcion: ";
            cin >> opcion;

            if (opcion == 1) {
                loggedIn = IniciarSesion();
            } else if (opcion == 2) {
                RegistrarUsuario();
                loggedIn = true;
            } else if (opcion == 0) {
                salir = true;
                break;
            } else {
                cout << "Opcion invalida \n";
            }
        }

        if (salir) break;

        cout << "\nSesion iniciada exitosamente.\n";

        do {
            cout << "\nElija una opcion:\n";
            cout << "1) Medir asistencia\n";
            cout << "2) Mostrar clases\n";
            cout << "3) Promedio\n";
            cout << "4) Hora hasta salida\n";
            cout << "5) Cambiar nombre de clase\n";
            cout << "6) Agregar clase\n";
            cout << "7) Eliminar clase\n";
            cout << "8) Eliminar usuario\n";
            cout << "0) Cerrar sesion\n";
            cin >> opcion;

            switch (opcion) {
                case 1:
                    Asistencia(); break;
                case 2:
                    MostrarClases(classes); break;
                case 3:
                    Promedio(classes); break;
                case 4:
                    HoraHastaSalida(); break;
                case 5:
                    CambiarNombreDeClase(classes); break;
                case 6:
                    AgregarClase(classes); break;
                case 7:
                    EliminarClase(classes); break;
                case 8:
                    EliminarUsuario(); break;
                case 0:
                    loggedIn = false;
                    cout << "Sesion cerrada.\n";
                    break;
                default:
                    cout << "Opcion no valida. Intente de nuevo.\n";
                    break;
            }

            if (loggedIn) {
                opc = SwitchReset();
            } else {
                opc = false;
            }

        } while (opc && loggedIn);

    } while (!salir);

}

