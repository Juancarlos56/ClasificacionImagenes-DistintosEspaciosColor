

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <math.h>
#include <sys/types.h>
#include <dirent.h>
#include <list>
#include <iterator>
#include <stdio.h>
#include <string.h>
#include <fstream>
// Librerías de OpenCV

//#include <opencv2/opencv.hpp>

#include <opencv2/core/core.hpp> // Contiene los elementos base de OpenCV (matrices, arreglos, etc.)
#include <opencv2/highgui/highgui.hpp> // Contiene estructuras para crear la interfaz gráfica
#include <opencv2/imgproc/imgproc.hpp> // Procesamiento de imágenes
#include <opencv2/imgcodecs/imgcodecs.hpp> // Códecs para leer determinados formatos de imágenes
#include <opencv2/video/video.hpp> // Procesamiento y escritura
#include <opencv2/videoio/videoio.hpp> // de video

using namespace std;
using namespace cv; // El espacio de nombres donde están definidas algunas funciones de OpenCV



double distanciaEuclidea(int *histo, int *histoCompare){
    
    double distancia, resta = 0;

    for (int i=0;i<256;i++){    //Bucle para restar componentes y elevarlas a 2
        resta=resta+pow(histo[i]- histoCompare[i],2);
    }
    return distancia=sqrt(resta);
}


void graficarHistograma(int maximo, int *histograma){
    // Representación gráfica del histograma
    int altoLienzo = 400;
    int anchoLienzo = 512;
    Mat lienzo = Mat(Size(anchoLienzo, altoLienzo), CV_8UC3, Scalar(255, 255, 255));

    double escala = ((double) altoLienzo)/((double) maximo);
    //cout << "Máximo valor histograma: " << maximo << " Escala: " << escala << endl;
    // line(lienzo, Point(lienzo.cols/2, lienzo.rows/2), Point(lienzo.cols,0), Scalar(0,0,255), 3);

    for (int i=0, j=0;i<256;i++,j+=2){
        rectangle(lienzo,Point(j, altoLienzo), Point(j+2,((double)altoLienzo)-(escala*((double)histograma[i]))), Scalar(10,240,240),2);
    }
    std::string s = std::to_string(maximo);
    namedWindow("Lienzo"+s,WINDOW_AUTOSIZE);
    imshow("Lienzo"+s, lienzo);
}

int imprimirHistograma(int *histo){
    int maximo = 0;
    for(int i=0;i<256;i++){
        cout << histo[i] << ",";
        if (histo[i]>maximo)
            maximo = histo[i];
    }

    cout << endl;
    return maximo;
}

void calcularHistogramaColorYcrCB(Mat image, int *histogramaYcrCB, int colorYcrCB){
    
    Vec3b voxel;
    int pixel = 0;
    //cout << "Columnas (ancho) = " << image.cols << " Filas (alto) = " << image. rows << " Canales: " << image.channels() << endl;
    for(int i=0;i<image.rows;i++){
        for(int j=0;j<image.cols;j++){
            voxel = image.at<Vec3b>(i,j);
            pixel = voxel[colorYcrCB];
            histogramaYcrCB[pixel]++;
        }
    }
}


void calculoHistograma(Mat image, int *histograma){
    int pixel = 0;
    for(int i=0;i<image.rows;i++){
        for(int j=0;j<image.cols;j++){
            pixel = (int) image.at<uchar>(i,j);
            histograma[pixel]++;
        }
    }
}

void calcularHistogramaColorHSV(Mat image, int *histogramaHSV, int colorHSV){
    
    Vec3b voxel;
    int pixel = 0;
    //cout << "Columnas (ancho) = " << image.cols << " Filas (alto) = " << image. rows << " Canales: " << image.channels() << endl;
    for(int i=0;i<image.rows;i++){
        for(int j=0;j<image.cols;j++){
            voxel = image.at<Vec3b>(i,j);
            pixel = voxel[colorHSV];
            histogramaHSV[pixel]++;
        }
    }
}


void calcularHistogramaColorRGB(Mat image, int *histogramaColor, int colorBGR){
    Vec3b voxel;
    int pixel = 0;

    for(int i=0;i<image.rows;i++){
        for(int j=0;j<image.cols;j++){
            voxel = image.at<Vec3b>(i,j);
            pixel = voxel[colorBGR];
            histogramaColor[pixel]++;
        }
    }
}



void calculoHistogramaGray(Mat image, int *histograma){

    Vec3b voxel;
    int pixel = 0;
    //Mat imgGris = Mat(Size(image.cols, image.rows), CV_8UC1, Scalar(255));
    //Mat imgGrisPesos = Mat(Size(image.cols, image.rows), CV_8UC1, Scalar(255));

    for(int i=0;i<image.rows;i++){
        for(int j=0;j<image.cols;j++){
            voxel = image.at<Vec3b>(i,j);
            pixel = voxel[2]*0.3+voxel[1]*0.59+voxel[0]*0.11;
            histograma[pixel]++;
            //imgGrisPesos.at<uchar>(i,j) = pixel;
        }
    }

}

void cargarHIstograma(int *histo){
    for(int i=0;i<256;i++)
        histo[i] = 0;

}


list <double> minValueDistanciaEuclidea(list <double> distanciaEuclidea, double distancia){
    if (distanciaEuclidea.empty()==false)
    {
        if(distanciaEuclidea.front() > distancia){
        distanciaEuclidea.pop_front();
        distanciaEuclidea.push_back(distancia);
        }
    }else{
        distanciaEuclidea.push_back(distancia);
    }

    return distanciaEuclidea;
}

class Categoria
{
private:
    string identificador;
    double distancia;
    string categorias;
    string espacioColor;
public:
    Categoria(double distancia, string categorias, string espacioColor, string identificador){
        this->distancia = distancia;
        this->categorias = categorias;
        this->espacioColor = espacioColor;
        this->identificador = identificador;
    }

    double getDIstancia() {
      return distancia;
    }

    string getCategoria() {
      return categorias;
    }

    string getEspacioColor() {
      return espacioColor;
    }
    
    string getIdentificador() {
      return identificador;
    }
};




class ImagenTest
{
private:
    string identificador;
    string categoria;
public:
    ImagenTest(string identificador, string categoria){
        this->identificador = identificador;
        this->categoria = categoria;
    }

    string getIdentificador() {
      return identificador;
    }

    string getCategoria() {
      return categoria;
    }
};

class Clasificacion
{
private:
    string identificador;
    string categoria;
    int clasificador;
public:
    Clasificacion(string identificador, string categoria, int clasificador){
        this->identificador = identificador;
        this->categoria = categoria;
        this->clasificador = clasificador;
    }

    string getIdentificador() {
      return identificador;
    }

    string getCategoria() {
      return categoria;
    }
    
    int getClasificador() {
      return clasificador;
    }
};


string deCharToString(char * cadena){
    stringstream ss;
    ss << cadena;

    return ss.str();
}

list <ImagenTest> read () {
    
    list <ImagenTest> listaImagenesTest;

    char ln[500], categoria;
    int cont = 0;
    ifstream read;
    const char *info[2] = {"ID: ", "Categoria: "};
    int pt = 0; 
    char * pch;
    char * cat;
    string id, tipoImagen;
    read.open ("imagenes/BSDS300/iids_test.txt", ios::out | ios::in);

    if (read.is_open())
    {    
        while (!read.eof())
        {
            // Obtiene linea del archivo
            read.getline(ln, 500);

            // Itemize la cadena para obtener cada uno de los elementos necesarios
            pch = strtok (ln,",");
            pt = 0;
            while (pch != NULL)
            {
                // Muestro el contenido de info para ver que los campos se obtiene de modo adecuado
                // pero tu deberias hacer el casteo correspondiente y asignar a variables.
                
                //string id(pch);
                id = deCharToString(pch);
                pch = strtok (NULL, " ");
                tipoImagen = deCharToString(pch);
                ImagenTest imagenRecuperada(id,tipoImagen);
                listaImagenesTest.push_back(imagenRecuperada);

                pch = strtok (NULL, "\n");
                
                pt ++;
                if(pt > 2)
                {
                    // En caso de que la cadena contengas mas campos de los que puedo procesar
                    break;
                }
            }

            cont ++;

        }
        cout<<"FINALIZA LECTURA DEL ARCHIVO TXT"<<endl;
    }
    else
    {
        cout << "¡Error! El archivo no pudo ser abierto." << endl;
    }

    read.close();
    return listaImagenesTest;

}


int main(int argc, char *argv[]){
    
    Mat imgCompare;
    Mat img;
    Mat imgGris;
    Mat imgGrisCompare;
    Mat imgHSV;
    Mat imgHSVCompare;
    Mat imgYcrCB;
    Mat imgCompareYcrCB;
    //Vector para matriz de espacio de color GRAY
    int *histo = new int[256];
    //Vectores para matriz de espacio de color RGB
    int *histoRojo = new int[256];
    int *histoAzul = new int[256];
    int *histoVerde = new int[256];
    //Vector para matriz de espacio de color HSV
    int *histoHue = new int[256];
    int *histoSaturation = new int[256];
    int *histoValue = new int[256];
    //Vector para matriz de espacio de color YcrCb
    int *histoY = new int[256];
    int *histoCr= new int[256];
    int *histoCb = new int[256];

    cargarHIstograma(histo);  
    cargarHIstograma(histoRojo);  
    cargarHIstograma(histoAzul);    
    cargarHIstograma(histoVerde);  
    cargarHIstograma(histoHue);  
    cargarHIstograma(histoSaturation);
    cargarHIstograma(histoValue);
    cargarHIstograma(histoY);  
    cargarHIstograma(histoCr);
    cargarHIstograma(histoCb);

    int *histoCompare = new int[256];
    int *histoCompareRojo = new int[256];
    int *histoCompareAzul = new int[256];
    int *histoCompareVerde = new int[256];
    int *histoCompareHue = new int[256];
    int *histoCompareSaturation = new int[256];
    int *histoCompareValue = new int[256];
    int *histoCompareY = new int[256];
    int *histoCompareCr= new int[256];
    int *histoCompareCb = new int[256];


    cargarHIstograma(histoCompare);
    cargarHIstograma(histoCompareRojo);  
    cargarHIstograma(histoCompareAzul);    
    cargarHIstograma(histoCompareVerde);  
    cargarHIstograma(histoCompareHue);  
    cargarHIstograma(histoCompareSaturation);
    cargarHIstograma(histoValue);
    cargarHIstograma(histoCompareY);  
    cargarHIstograma(histoCompareCr);
    cargarHIstograma(histoCompareCb);
    

    list <double> listaDistanciaEuclideaGray;
    list <double> listaDistanciaEuclideaRGB;
    list <double> listaDistanciaEuclideaHSV;
    list <double> listaDistanciaEuclideaYcrCB;


    list <Categoria> listaMenorDistanciaGray;
    list <Categoria> listaMenorDistanciaRGB;
    list <Categoria> listaMenorDistanciaHSV;
    list <Categoria> listaMenorDistanciaYcrCB;


    list <Categoria> listaDistanciaEuclideaParaCategoria;
    list <Categoria> listaDistanciaEuclideaPorCategoriaResultadosGRAY;
    list <Categoria> listaDistanciaEuclideaPorCategoriaResultadosHSV;
    list <Categoria> listaDistanciaEuclideaPorCategoriaResultadosRGB;
    list <Categoria> listaDistanciaEuclideaPorCategoriaResultadosYcrCB;



    double distanciaImage, distancia;
    double distanciaCompare;
    double distanciaRGB;
    double distanciaGray;
    double distanciaHSV;
    double distanciaYcrCB;
    int cantidadImagenes = 0; 
    int cantidadImagenesTrain = 0; 

    //FILE *fichero;
    string resultado = "";
            

    /* Con un puntero a DIR abriremos el directorio */
    DIR *dir, *dirTrain;
    /* en *ent habrá información sobre el archivo que se está "sacando" a cada momento */
    struct dirent *ent, *entTrain;



    const char *PATH_TEST ={ "imagenes/BSDS300/images/test/"};
    // Initialize array of pointer
    const char *PATHS[4] = { "imagenes/BSDS300/images/train/animales/", "imagenes/BSDS300/images/train/paisaje/",
                             "imagenes/BSDS300/images/train/personas/", "imagenes/BSDS300/images/train/plantas/" };
    //Categorias de clasificacion
    const char *Categorias[4] = {"Animales", "Paisaje", "Personas", "Plantas"};

    
    /* Empezaremos a leer en el directorio actual */
    dir = opendir (PATH_TEST);

    /* Miramos que no haya error */
    if (dir == NULL)
        cout<<"No puedo abrir el directorio"<<endl;

    /* Leyendo uno a uno todos los archivos que hay */
    int cont2=0, cont = 0;
    while (((ent = readdir (dir)) != NULL )){

        /* Nos devolverá el directorio actual (.) y el anterior (..), como hace ls */
        if ( strcmp(ent->d_name, PATH_TEST)!=0 ){
            /* Una vez tenemos el archivo, lo pasamos a una función para procesarlo. */

            char *pathImagenTest = ent->d_name;
            string pathImagenTestString(pathImagenTest);

            if ((pathImagenTestString != ".")&&(pathImagenTestString != ".."))
            {
                cout<<"<<<<<<<<<<<<<<<<<" <<PATH_TEST+pathImagenTestString <<">>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;
                img = imread(PATH_TEST+pathImagenTestString);

                for (int i = 0; i < 4; i++){
        
                    // Empezaremos a leer en el directorio actual 
                    dirTrain = opendir (PATHS[i]);

                    // Miramos que no haya error 
                    if (dirTrain == NULL){
                        cout<<"No puedo abrir el directorio"<<endl;
                    }
                        
                    // Leyendo uno a uno todos los archivos que hay 
                    while (((entTrain = readdir (dirTrain)) != NULL) ){

                        // Nos devolverá el directorio actual (.)  
                        if ( strcmp(entTrain->d_name, PATHS[i]) < 0 ){
                            
                            
                            char *pathImagenTrain = entTrain->d_name;
                            string pathImagenTrainString(pathImagenTrain);
                            
                            if ((pathImagenTrainString != ".") && (pathImagenTrainString != ".."))
                            {
                                imgCompare = imread(PATHS[i]+pathImagenTrainString);

                                
                                

                                //Comparacion de distancia euclidea con respecto a espacio de color RGB. 
                                //1. Calcular Histograma para los espacios de color Azul, verde y rojo. 
                                //1.1 Histograma color AZUL
                                calcularHistogramaColorRGB(img, histoAzul, 2);
                                calcularHistogramaColorRGB(imgCompare, histoCompareAzul, 2);
                                //1.2 Histograma color Verde
                                calcularHistogramaColorRGB(img, histoVerde, 1);
                                calcularHistogramaColorRGB(imgCompare, histoCompareVerde, 1);
                                //1.3 Histograma color Rojo
                                calcularHistogramaColorRGB(img, histoRojo, 0);
                                calcularHistogramaColorRGB(img, histoCompareRojo, 0);
                                //2. Calculo de distancia total mediante la suma de las distancias de los histogramas RGB
                                distanciaRGB = distanciaEuclidea(histoAzul, histoCompareAzul)
                                            + distanciaEuclidea(histoVerde, histoCompareVerde) 
                                            + distanciaEuclidea(histoRojo, histoCompareRojo);
                                listaDistanciaEuclideaRGB = minValueDistanciaEuclidea(listaDistanciaEuclideaRGB, distanciaRGB);

                                //Comparacion de distancia euclidea con respecto a espacio de color GRAY
                                //1. Calculo de histograma para imagen original a color que se transforma a escala de grisis
                                calculoHistogramaGray(img, histo);
                                //2. Calculo de histograma para imagen a ser comparada con la imagen original a color que se transforma a escala de grisis
                                calculoHistogramaGray(imgCompare, histoCompare);
                                //3. Calculo de la distancia euclidea entre las dos imagenes a escala de grises.  
                                distanciaGray = distanciaEuclidea(histo, histoCompare);
                                listaDistanciaEuclideaGray = minValueDistanciaEuclidea(listaDistanciaEuclideaGray, distanciaGray);


                                //Comparacion de distancia euclidea con respecto a espacio de color HSV 
                                //1. Cambio de espacios de color de BGR TO HSV
                                cvtColor(img, imgHSV, COLOR_BGR2HSV);
                                cvtColor(imgCompare, imgHSVCompare, COLOR_BGR2HSV);
                                //2. Calculo de histogramas
                                //2.1 Calculo de espacio HUE rango 0-180
                                calcularHistogramaColorHSV(imgHSV, histoHue, 0);
                                calcularHistogramaColorHSV(imgHSVCompare, histoCompareHue, 0);
                                //2.2 Calcilo de espacio Saturacion rango 0-256
                                calcularHistogramaColorHSV(imgHSV, histoSaturation, 1);
                                calcularHistogramaColorHSV(imgHSVCompare, histoCompareSaturation, 1);
                                //2.3 Calculo de espacio Value rango 0-256
                                calcularHistogramaColorHSV(imgHSV, histoValue, 2);
                                calcularHistogramaColorHSV(imgHSVCompare, histoCompareValue, 2);
                                //3. Calculo de distancia HSV
                                distanciaHSV = distanciaEuclidea(histoHue, histoCompareHue)
                                                + distanciaEuclidea(histoSaturation, histoCompareSaturation) 
                                                + distanciaEuclidea(histoValue, histoCompareValue);
                                listaDistanciaEuclideaHSV = minValueDistanciaEuclidea(listaDistanciaEuclideaHSV, distanciaHSV);



                                //Comparacon de distancia Euclidea con respecto a espacio de color YcrCb
                                //1.Cambio de espacio de color de BGR TO YcrCb
                                cvtColor(img, imgYcrCB, COLOR_BGR2YCrCb);
                                cvtColor(imgCompare, imgCompareYcrCB, COLOR_BGR2YCrCb);
                                //2. Calculo de Histogramas
                                //2.1 Calculo de espacio Y 
                                calcularHistogramaColorYcrCB(imgYcrCB, histoY, 0);
                                calcularHistogramaColorYcrCB(imgCompareYcrCB, histoCompareY, 0);
                                //2.1 Calculo de espacio Cr
                                calcularHistogramaColorYcrCB(imgYcrCB, histoCr, 1);
                                calcularHistogramaColorYcrCB(imgCompareYcrCB, histoCompareCr, 1);
                                //2.1 Calculo de espacio Cb
                                calcularHistogramaColorYcrCB(imgYcrCB, histoCb, 2);
                                calcularHistogramaColorYcrCB(imgCompareYcrCB, histoCompareCb, 2);
                                //3. Calculo de la distancia YcrCB
                                distanciaYcrCB = distanciaEuclidea(histoY, histoCompareY)
                                                + distanciaEuclidea(histoCr, histoCompareCr) 
                                                + distanciaEuclidea(histoCb, histoCompareCb);
                                listaDistanciaEuclideaYcrCB = minValueDistanciaEuclidea(listaDistanciaEuclideaYcrCB, distanciaYcrCB);


                                //cout << '\t' <<"RGB: "<< distanciaRGB << '\t'<<"GRAY: "<<distanciaGray<<'\t'<<"HSV: "<<distanciaHSV<<'\t'<< "YcrCB: "<<distanciaYcrCB<<endl;



                                // Se verifica si el valor de la lista es mayor o menor.
                                // si el valor es menor al enterior se modifica y guardamos en la lista.
                                // si es valor es mayor se mantiene este valor hasta encontrar uno menor. 
                                // si la lista esta vacia se agrega este primer valor directamente. 
                                /*
                                if (listaDistanciaEuclidea.empty()==false)
                                {
                                    if(listaDistanciaEuclidea.front() > distanciaTotal){
                                    listaDistanciaEuclidea.pop_front();
                                    listaDistanciaEuclidea.push_back(distanciaTotal);
                                    }
                                }else{
                                    listaDistanciaEuclidea.push_back(distanciaTotal);
                                }
                                */
                                //Borro cualquier histograma que se almaceno para comenzar como valores de cero en todo el histograma. 
                                cargarHIstograma(histo);
                                cargarHIstograma(histoAzul);
                                cargarHIstograma(histoVerde);
                                cargarHIstograma(histoRojo);
                                cargarHIstograma(histoY);
                                cargarHIstograma(histoCr);
                                cargarHIstograma(histoCb);
                                cargarHIstograma(histoCompare);
                                cargarHIstograma(histoHue);
                                cargarHIstograma(histoSaturation);
                                cargarHIstograma(histoValue);


                                cargarHIstograma(histoCompareAzul);
                                cargarHIstograma(histoCompareVerde);
                                cargarHIstograma(histoCompareRojo);
                                cargarHIstograma(histoCompareY);
                                cargarHIstograma(histoCompareCb);
                                cargarHIstograma(histoCompareCr);
                                cargarHIstograma(histoCompareHue);
                                cargarHIstograma(histoCompareSaturation);
                                cargarHIstograma(histoCompareValue);

                                //cont2++;
                                cantidadImagenesTrain++;
                            }
                            
                        }

                        

                    }


                    //Creacion de objetos de tipo categoria para ver las distancia en cada imagen
                    Categoria categoriaObtenidaGray(listaDistanciaEuclideaGray.front() , Categorias[i], "GRAY", pathImagenTestString);
                    Categoria categoriaObtenidaRGB(listaDistanciaEuclideaRGB.front() , Categorias[i], "RGB", pathImagenTestString);
                    Categoria categoriaObtenidaHSV(listaDistanciaEuclideaHSV.front() , Categorias[i], "HSV", pathImagenTestString);
                    Categoria categoriaObtenidaYcrCB(listaDistanciaEuclideaYcrCB.front() , Categorias[i], "YcrCB", pathImagenTestString);

                    //Asignacion de la categoria a la lista de resultados
                    listaDistanciaEuclideaParaCategoria.push_back(categoriaObtenidaGray);
                    listaDistanciaEuclideaParaCategoria.push_back(categoriaObtenidaRGB);
                    listaDistanciaEuclideaParaCategoria.push_back(categoriaObtenidaHSV);
                    listaDistanciaEuclideaParaCategoria.push_back(categoriaObtenidaYcrCB);

                    //Limpiamos las listas para la nueva imagen de distitnos directorio a ingresar
                    listaDistanciaEuclideaGray.clear();
                    listaDistanciaEuclideaRGB.clear();
                    listaDistanciaEuclideaHSV.clear();
                    listaDistanciaEuclideaYcrCB.clear();

                    closedir (dirTrain);
                
        
                }
            }
            

            
            
            cont++;
            //Codigo para imprimir en pantalla los resultados de todos los directorios
            /*
            list <Categoria> :: iterator it;

            int contador = 0;
            for(it = listaDistanciaEuclideaParaCategoria.begin(); it != listaDistanciaEuclideaParaCategoria.end(); ++it){
                if (contador < 4)
                {
                    cout  << '\t' <<it->getEspacioColor() << ":"<< it->getCategoria()<< " : "<<it->getDIstancia()<<'\t';   
                    contador++; 
                }else
                {
                    cout<<'\n'; 
                    cout  << '\t' <<it->getEspacioColor() << ":"<< it->getCategoria()<< " : "<<it->getDIstancia()<<'\t'; 
                    contador = 1;   
                }
            }
            cout << endl;
            */
            
            //Debido a que cada directorio va a tener su propio resultado lo que hacemos es 
            //ver cual es el menor de este para asignar el valor de clasificador por ejemplo
            //paisajeHSV = 5        paisajeRGB = 2  ...
            //animalesHSV = 6       animalesRGB = 6    ...   
            //personasHSV = 4       personasRGB = 4 ...
            //plantasHSV = 5        plantasRGB = 3  ...
            //Enconces lo que se hace es escojer el minimo valor por categoria en este ejemplo seria 
            //para HSV: personasHSV=4   para RGB: paisajeRGB=2
            list <Categoria> :: iterator it;
            for(it = listaDistanciaEuclideaParaCategoria.begin(); it != listaDistanciaEuclideaParaCategoria.end(); ++it){
                if ( (it->getEspacioColor() == "GRAY") )
                {
                    if (listaMenorDistanciaGray.empty())
                    {
                        listaMenorDistanciaGray.push_back(*it);
                    }else if(listaMenorDistanciaGray.front().getDIstancia() > it->getDIstancia()){
                            listaMenorDistanciaGray.pop_front();
                            listaMenorDistanciaGray.push_back(*it);
                    }
                            
                }else if((it->getEspacioColor() == "RGB")){
                    if (listaMenorDistanciaRGB.empty())
                    {
                        listaMenorDistanciaRGB.push_back(*it);
                    }else if(listaMenorDistanciaRGB.front().getDIstancia() > it->getDIstancia()){
                            listaMenorDistanciaRGB.pop_front();
                            listaMenorDistanciaRGB.push_back(*it);
                    }
                }else if((it->getEspacioColor() == "HSV")){
                    if (listaMenorDistanciaHSV.empty())
                    {
                        listaMenorDistanciaHSV.push_back(*it);
                    }else if(listaMenorDistanciaHSV.front().getDIstancia() > it->getDIstancia()){
                            listaMenorDistanciaHSV.pop_front();
                            listaMenorDistanciaHSV.push_back(*it);
                    }
                }else if((it->getEspacioColor() == "YcrCB")){
                    if (listaMenorDistanciaYcrCB.empty())
                    {
                        listaMenorDistanciaYcrCB.push_back(*it);
                    }else if(listaMenorDistanciaYcrCB.front().getDIstancia() > it->getDIstancia()){
                            listaMenorDistanciaYcrCB.pop_front();
                            listaMenorDistanciaYcrCB.push_back(*it);
                    }
                }
            }

            for(it = listaMenorDistanciaGray.begin(); it != listaMenorDistanciaGray.end(); ++it){
                listaDistanciaEuclideaPorCategoriaResultadosGRAY.push_back(*it);
            }
            for(it = listaMenorDistanciaRGB.begin(); it != listaMenorDistanciaRGB.end(); ++it){
                listaDistanciaEuclideaPorCategoriaResultadosRGB.push_back(*it);
            }
            for(it = listaMenorDistanciaHSV.begin(); it != listaMenorDistanciaHSV.end(); ++it){
                listaDistanciaEuclideaPorCategoriaResultadosHSV.push_back(*it);
            }
            for(it = listaMenorDistanciaYcrCB.begin(); it != listaMenorDistanciaYcrCB.end(); ++it){
                listaDistanciaEuclideaPorCategoriaResultadosYcrCB.push_back(*it);
            }
            
    
            //procesoArchivo(ent->d_name);
            
            listaDistanciaEuclideaParaCategoria.clear();
            listaMenorDistanciaGray.clear();
            listaMenorDistanciaRGB.clear();
            listaMenorDistanciaHSV.clear();
            listaMenorDistanciaYcrCB.clear();

            //listaDistanciaEuclideaPorCategoriaResultados.clear();
            //cantidadImagenes++;
        }
    }
    closedir (dir);
    

    list<ImagenTest> imagesTest= read();
    cout<<""<<endl;
    list <ImagenTest> :: iterator iter;   
    list <Categoria> :: iterator iterad;   

    list<Clasificacion> clasificarYcrCB;
    list<Clasificacion> clasificarHSV;
    list<Clasificacion> clasificarRGB;
    list<Clasificacion> clasificarGRAY;
    int contClasifiacionCorrectaGRAY = 0;  
    int contClasifiacionCorrectaRGB = 0;    
    int contClasifiacionCorrectaHSV = 0;    
    int contClasifiacionCorrectaYcrCB = 0;    
    
    //Clasificacion de Imagenes
    for(iter = imagesTest.begin(); iter != imagesTest.end(); ++iter){
        
        //Clasificacion de imagenes YcrCB
        for(iterad = listaDistanciaEuclideaPorCategoriaResultadosYcrCB.begin(); 
            iterad != listaDistanciaEuclideaPorCategoriaResultadosYcrCB.end(); 
            ++iterad){
            
            if (iterad->getIdentificador() == iter->getIdentificador())
            {
                if (iterad->getCategoria() == iter->getCategoria())
                {
                    Clasificacion cl(iterad->getIdentificador(), iterad->getCategoria(), 1);
                    clasificarYcrCB.push_back(cl);
                    contClasifiacionCorrectaYcrCB++;
                }else{
                    Clasificacion cl(iterad->getIdentificador(), iterad->getCategoria(), 0);
                    clasificarYcrCB.push_back(cl);
                }

                
            }
            
        }

        //Clasificacion de imagenes RGB
        for(iterad = listaDistanciaEuclideaPorCategoriaResultadosRGB.begin(); 
            iterad != listaDistanciaEuclideaPorCategoriaResultadosRGB.end(); 
            ++iterad){
            
            if (iterad->getIdentificador() == iter->getIdentificador())
            {
                if (iterad->getCategoria() == iter->getCategoria())
                {
                    Clasificacion cl(iterad->getIdentificador(), iterad->getCategoria(), 1);
                    clasificarRGB.push_back(cl);
                    contClasifiacionCorrectaRGB++;
                }else{
                    Clasificacion cl(iterad->getIdentificador(), iterad->getCategoria(), 0);
                    clasificarRGB.push_back(cl);
                }
            }
            
        }       

        //Clasificacion de imagenes HSV
        for(iterad = listaDistanciaEuclideaPorCategoriaResultadosHSV.begin(); 
            iterad != listaDistanciaEuclideaPorCategoriaResultadosHSV.end(); 
            ++iterad){
            
            if (iterad->getIdentificador() == iter->getIdentificador())
            {
                if (iterad->getCategoria() == iter->getCategoria())
                {
                    Clasificacion cl(iterad->getIdentificador(), iterad->getCategoria(), 1);
                    clasificarHSV.push_back(cl);
                    contClasifiacionCorrectaHSV++;
                }else{
                    Clasificacion cl(iterad->getIdentificador(), iterad->getCategoria(), 0);
                    clasificarHSV.push_back(cl);
                }
            }
            
        }       

        //Clasificacion de imagenes GRAY
        for(iterad = listaDistanciaEuclideaPorCategoriaResultadosGRAY.begin(); 
            iterad != listaDistanciaEuclideaPorCategoriaResultadosGRAY.end(); 
            ++iterad){
            
            if (iterad->getIdentificador() == iter->getIdentificador())
            {
                if (iterad->getCategoria() == iter->getCategoria())
                {
                    Clasificacion cl(iterad->getIdentificador(), iterad->getCategoria(), 1);
                    clasificarGRAY.push_back(cl);
                    contClasifiacionCorrectaGRAY++;
                }else{
                    Clasificacion cl(iterad->getIdentificador(), iterad->getCategoria(), 0);
                    clasificarGRAY.push_back(cl);
                }
            }
            
        }       
    }

    cout<<"SIZE GRAY: "<<clasificarGRAY.size()<<endl;
    cout<<"SIZE RGB: "<<clasificarRGB.size()<<endl;
    cout<<"SIZE HSV: "<<clasificarHSV.size()<<endl;
    cout<<"SIZE YcrCB: "<<clasificarYcrCB.size()<<endl;
    

    
    //auto str = std::to_string(42.5); 

    cout<<"------------------------------RESULTADOS--------------------------------"<<endl;
    
    cout<<"<<<<<<<<<<<PRESICION ESPACIO COLOR GRAY>>>>>>>>>>>>>>>>"<<endl;
    cout<<"Clasificados Correctamente: "<<contClasifiacionCorrectaGRAY 
    <<" Clasificados Incorrectamente: "<<clasificarGRAY.size()-contClasifiacionCorrectaGRAY 
    <<" Presicion: " <<  to_string((double)contClasifiacionCorrectaGRAY/(double)clasificarGRAY.size())<<endl;
    
    cout<<"<<<<<<<<<<<PRESICION ESPACIO COLOR RGB>>>>>>>>>>>>>>>>"<<endl;
    cout<<"Clasificados Correctamente: "<<contClasifiacionCorrectaRGB 
    <<" Clasificados Incorrectamente: "<<clasificarRGB.size()-contClasifiacionCorrectaRGB 
    <<" Presicion: " << to_string((double)contClasifiacionCorrectaRGB/(double)clasificarRGB.size())<<endl;
    
    cout<<"<<<<<<<<<<<PRESICION ESPACIO COLOR HSV>>>>>>>>>>>>>>>>"<<endl;
    cout<<"Clasificados Correctamente: "<<contClasifiacionCorrectaHSV 
    <<" Clasificados Incorrectamente: "<<clasificarHSV.size()-contClasifiacionCorrectaHSV 
    <<" Presicion: " << to_string((double)contClasifiacionCorrectaHSV/(double)clasificarHSV.size())<<endl;
    
    cout<<"<<<<<<<<<<<PRESICION ESPACIO COLOR YcrCB>>>>>>>>>>>>>>>>"<<endl;
    cout<<"Clasificados Correctamente: "<<contClasifiacionCorrectaYcrCB 
    <<" Clasificados Incorrectamente: "<<clasificarYcrCB.size()-contClasifiacionCorrectaYcrCB 
    <<" Presicion: " << to_string((double)contClasifiacionCorrectaYcrCB/(double)clasificarYcrCB.size())<<endl;

   

    
    // Representación gráfica 
    int *grafica = new int[100];

    for(int i=0;i<100;i++){
        if (i==10){
            grafica[i] = (double)contClasifiacionCorrectaGRAY;
        }else if (i==15){
            grafica[i] = (double)clasificarGRAY.size()-contClasifiacionCorrectaGRAY;
        }else if (i==20){
            grafica[i] = ((double)contClasifiacionCorrectaGRAY/(double)clasificarGRAY.size())*double(100);
        }else if (i == 30){
            grafica[i] = (double)contClasifiacionCorrectaRGB;
        }else if (i == 35){
            grafica[i] = (double)clasificarRGB.size()-contClasifiacionCorrectaRGB;
        }else if (i == 40){
            grafica[i] = ((double)contClasifiacionCorrectaRGB/(double)clasificarRGB.size())*double(100);
        }else if (i == 50){
            grafica[i] = (double)contClasifiacionCorrectaHSV;
        }else if (i == 55){
            grafica[i] = (double)clasificarHSV.size()-contClasifiacionCorrectaHSV;
        }else if (i == 60){
            grafica[i] = ((double)contClasifiacionCorrectaHSV/(double)clasificarHSV.size())*double(100);
        }else if (i == 70){
            grafica[i] = (double)contClasifiacionCorrectaYcrCB;
        }else if (i == 75){
            grafica[i] = (double)clasificarYcrCB.size()-contClasifiacionCorrectaYcrCB;
        }else if (i == 80){
            grafica[i] = ((double)contClasifiacionCorrectaYcrCB/(double)clasificarYcrCB.size())*double(100);
        }else{
            grafica[i] = 0;
        }
        
        
        
    }
        

    int altoLienzo = 400;
    int anchoLienzo = 256;
    Mat lienzo = Mat(Size(anchoLienzo, altoLienzo),  CV_8UC3, Scalar(255, 255, 255));
    
    double escala = ((double) altoLienzo)/((double) clasificarGRAY.size());
    cout << "Máximo valor histograma: " << (double) clasificarGRAY.size() << " Escala: " << escala << endl;

    for (int i=0, j=0;i<100;i++,j+=2){
        
        
        rectangle(lienzo,Point(j, altoLienzo), Point(j+2,((double)altoLienzo)-(escala*((double)grafica[i]))), Scalar(10,240,240), 5);
    }
    
    namedWindow("ComparacionEspacioColor",WINDOW_AUTOSIZE);
    imwrite("Imagen-ComparacionEspacioColor.jpg", lienzo);
    imshow("ComparacionEspacioColor", lienzo);
    
    waitKey(0); 

    destroyAllWindows(); // Cierra todas las ventanas que se hayan creado en el programa

    delete [] histo;

    return 0;
}





