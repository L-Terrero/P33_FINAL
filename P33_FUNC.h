#ifndef P33_FUNC_H
#define P33_FUNC_H

#include <string>
#include <vector>

using namespace std;


extern const string CREDENCIALES_FILEPATH;
extern const string CLASSES_FILEPATH;

void RevisionYGuardadoDeClases();
vector<string> CargarClases();
void GuardarClases(const vector<string>& classes);
void hora();
void RegistrarUsuario();
bool IniciarSesion();
void CambiarNombreDeClase(vector<string>& classes);
void AgregarClase(vector<string>& classes);
void EliminarClase(vector<string>& classes);
void MostrarClases(const vector<string>& classes);
void Asistencia();
void Promedio(const vector<string>& classes);
void HoraHastaSalida();
void EliminarUsuario();
bool SwitchReset();

#endif // P33_FUNC_H
