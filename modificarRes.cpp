
#include <tchar.h>
#include <stdio.h>
#include <windows.h>
#include <iostream>
using namespace std;
int main(void){
    TCHAR ruta[MAX_PATH];
    DWORD logitudRuta = 0;
    // GetModuleFileName retorna el numero de caracteres
    logitudRuta = GetModuleFileName(NULL, ruta, MAX_PATH);
    if (logitudRuta == 0){
        _tprintf(TEXT("No se pudo encontrar el nombre del archivo del modulo , %lu\n"), GetLastError());
        return -1;
    }
    HKEY nuevoValorClave;
    //Aqui habre el registro
    if (RegOpenKey(HKEY_LOCAL_MACHINE,
                   TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Run"),
                   //La linea de arriba es de los programas que inician con windows
                   &nuevoValorClave) != ERROR_SUCCESS)
    {
        _tprintf(TEXT("No se pudo abrir el registro = %lu\n"), GetLastError());
        return -1;
    }
    /* Hay que pasar la longitud de la cadena de la ruta declarada el principio en bytes
    Aqui es donde se empieza a asignar el nuevo valor de la clave del registro
    */
    DWORD logitudRutaEnBytes = logitudRuta * sizeof(*ruta);
    if (RegSetValueEx(nuevoValorClave,
                      TEXT("name_me"),
                      0,
                      REG_SZ,
                      (LPBYTE)ruta,
                      logitudRutaEnBytes) != ERROR_SUCCESS)
    {
        RegCloseKey(nuevoValorClave);
        _tprintf(TEXT("No se pudo asignar el valor %lu\n"), GetLastError());
        return -1;
    }
    int x;
    RegCloseKey(nuevoValorClave);
    cout << "El registro de modifico";
    cin >> x;
    return 0;
}