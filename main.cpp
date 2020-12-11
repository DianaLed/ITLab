#include <iostream>
#include <fstream>
#include <string>

#include "Inp.h"
#include "Layer.h"
#include "math.h"
//#include "Layer_for_all_pic.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace std;
using namespace cv;
Inp<double> In_img[784];
Layer<double> layer0(784);
Layer<double> layer1(16);
Layer<double> layer2(16);
Layer<double> layer3(10);
double wes1[16][784], wes2[16][16], wes3[10][16];
Mat img;
string addres_to_doc = "C:\\projects\\ITLab\\dop\\Itog\\tmp\\Debug\\doc\\"; //обязательно, что бы все адреса заканчивались "\\", так как
string addres_to_mnist_training = "C:\\projects\\ITLab\\dop\\Itog\\tmp\\Debug\\mnist_png\\training\\";//сразу за ними идут или названия  
                                                                                                     //файлов, или папки
string addres_to_mnist_testing = "C:\\projects\\ITLab\\dop\\Itog\\tmp\\Debug\\mnist_png\\testing\\";
double learning_rate = 1, bias=-0.001;
string all_adress_for_training(int nom_pict, int nom_group) {
  string s_nom = to_string(nom_pict) + ".png";
  string group = to_string(nom_group) + "\\";
  string res = addres_to_mnist_training + group;
  res = res + s_nom;
  return res;
}
string all_adress_for_testing(int nom_pict, int nom_group) {
  string s_nom = to_string(nom_pict) + ".png";
  string group = to_string(nom_group) + "\\";
  string res = addres_to_mnist_testing + group;
  res = res + s_nom;
  return res;
}

double sigm(double a) {
  double res = 1 / (1 + exp((-1)*a));
  return res;
}


bool ceach_file_png(string addres) {
  ifstream file;
  file.open(addres);
  if (!file) {   
    file.close();
    return 0;
  } 
  file.close();
  return 1;
}
int ceach_file_training_group_png(int nom_pick) {
  for (int i = 0; i < 10; i++) {
    if (ceach_file_png(all_adress_for_training(nom_pick, i))) return i;
  }
  return -1;
}
int ceach_file_testing_group_png(int nom_pick) {
  for (int i = 0; i < 10; i++) {
    if (ceach_file_png(all_adress_for_testing(nom_pick, i))) return i;
  }
  return -1;
}


double ran_chislo() {
  double s;
  s = rand() % 100;
  s = s/ 100 ;
  return s;
}

double ran_chislo_0() {
  double s;
  s = rand() % 100;
  s = s / 100;
  return s;
}

void all_rand_wes() {
  //вес1
  for (int i = 0; i < 16; i++) {
    for (int j = 0; j < 784; j++) {
      wes1[i][j]= ran_chislo_0();
    }
  }
  //вес2
  for (int i = 0; i < 16; i++) {
    for (int j = 0; j < 16; j++) {
      wes2[i][j] = ran_chislo_0();
    }
  }
  //вес3
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 16; j++) {
      wes3[i][j] = ran_chislo_0();
    }
  }
}
void wes_in_layer(int nom_layer, int nom_p) {
  if (nom_layer == 1) {
    for (int i = 0; i < 784; i++) {
      layer0[i].ChangeW(wes1[nom_p][i]);
    }
  }
  if (nom_layer == 2) {
    for (int i = 0; i < 16; i++) {
      layer1[i].ChangeW(wes2[nom_p][i]);
    }
  }
  if (nom_layer == 3) {
    for (int i = 0; i < 16; i++) {
      layer2[i].ChangeW(wes3[nom_p][i]);
    }
  }
}

void vqv_img_in_layer(Layer<double> *l) {
  int dop = 0;
  if (l->get_size() > 600) {
    for (int i = 0; i < 28; i++) {
      for (int j = 0; j < 28; j++) {
        cout << l->get_imp(dop).getW() << " ";
        dop++;
      }
      cout << endl;
    }
    cout << endl;
  }
}



void read_new_img(string name) {
  string image_path = samples::findFile(name);
  img = imread(image_path, IMREAD_COLOR);
  if (img.empty())
  {
    std::cout << "Could not read the image: " << name << endl;
  }
  else cvtColor(img, img, COLOR_BGR2GRAY);

  int dop = 0;
  int a = 0;
  for (int i = 0; i < 28; i++) {
    for (int j = 0; j < 28; j++) {
      dop = img.at<uchar>(i, j);
      if (dop == 0) layer0[a].ChangeXW(0, 0);
      else layer0[a].ChangeXW(1, 0);
      a++;
    }
  }
}

void work_with_l(int num_l) {
  double sum = 0;
  if (num_l == 1) {
    for (int i = 0; i < layer1.get_size(); i++) {
      wes_in_layer(num_l, i);
      sum = 0;
      for (int j = 0; j < layer0.get_size(); j++) {
        sum=sum+layer0.get_XW(j);
      }
      //cout << sum << " ";
      layer1.input_inp(i, sigm(sum+ bias), 0); //все-равно перед работой нужные веса заново вбиваются
    }
  }
  if (num_l == 2) {
    for (int i = 0; i < layer2.get_size(); i++) {
      wes_in_layer(num_l, i);
      sum = 0;
      for (int j = 0; j < layer1.get_size(); j++) {
        sum = sum + layer1.get_XW(j);
      }
      /*cout << sum << " ";*/
      layer2.input_inp(i, sigm(sum+ bias), 0); //все-равно перед работой нужные веса заново вбиваются
    }
  }
  if (num_l == 3) {
    for (int i = 0; i < layer3.get_size(); i++) {
      wes_in_layer(num_l, i);
      sum = 0;
      for (int j = 0; j < layer2.get_size(); j++) {
        sum = sum + layer2.get_XW(j);
      }
      /*cout << sum << " ";*/
      layer3.input_inp(i, sigm(sum+ bias), 0); //все-равно перед работой нужные веса заново вбиваются
    }
  }
  //cout << endl;
}

double consider_weight_delta(double error, double sigm_x) {
  return (error * sigm_x * (1 - sigm_x)); //производная от сигмоиды  sigm_x * (1 - sigm_x)
}

bool it_is_zero(double chislo) {
  if ((chislo < 0.019) && (chislo > 0)) return 1; //0.016
  return 0;
}

bool it_is_one(double chislo) {
  if ((chislo > 0.9) && (chislo < 1.1)) return 1; 
  return 0;
}

void study_9_zero(int res_no_zero) {
  bool r = 1;
  int dop = 0;
  double error, weight_delta;
  int q = 0;
  for (int a = 0; a < 10; a++) {
    if (a != res_no_zero) {
      q = 0;
      if (!(it_is_zero(layer3[a].getX()))) {
        error = layer3[a].getX();
        weight_delta = consider_weight_delta(error, layer3[a].getX());
        for (int i = 0; i < layer2.get_size(); i++) {
          wes3[a][i] = wes3[a][i] - layer2[i].getX() * weight_delta * learning_rate;
        }
        //прописали третий уровень
        for (int i = 0; i < layer2.get_size(); i++) { //для прохода по слою
          error = layer2[a].getX() - layer2[a].getLX();
          weight_delta = consider_weight_delta(error, layer2[i].getX());
          for (int j = 0; j < layer1.get_size(); j++) { //для прохода по весам
            wes2[i][j] = wes2[i][j] - layer1[i].getX() * weight_delta * learning_rate;
          }
        }
        //прописали второй уровень
        for (int i = 0; i < layer1.get_size(); i++) { //для прохода по слою
          error = layer1[a].getX() - layer1[a].getLX();
          weight_delta = consider_weight_delta(error, layer1[i].getX());
          for (int j = 0; j < layer0.get_size(); j++) { //для прохода по весам
            wes1[i][j] = wes1[i][j] - layer0[i].getX() * weight_delta * learning_rate;
          }
        }
        for (int i = 1; i < 4; i++) work_with_l(i);
        error = layer3[a].getX();
        /*cout << q << "- " << error << endl;*/
        q++;
        /*if (q > 3000) break;*/
      }
    }
  }
}

void study_1_one(int res) {
  bool r = 1;
  int dop = 0;
  double error, weight_delta;
  int q = 0;
  if (!(it_is_one(layer3[res].getX()))) {
    error = layer3[res].getX() - 1; //-1 ожидаемый результат
    /*q++;
    cout << q << "-" << layer3[res].getX() << endl;*/
    weight_delta = consider_weight_delta(error, layer3[res].getX());
    for (int i = 0; i < layer2.get_size(); i++) {
      wes3[res][i] = wes3[res][i] - layer2[i].getX() * weight_delta * learning_rate;
    }
    //прописали третий уровень
    for (int i = 0; i < layer2.get_size(); i++) { //для прохода по слою
      error = layer2[res].getX() - layer2[res].getLX();
      weight_delta = consider_weight_delta(error, layer2[i].getX());
      for (int j = 0; j < layer1.get_size(); j++) { //для прохода по весам
        wes2[i][j] = wes2[i][j] - layer1[i].getX() * weight_delta * learning_rate;
      }
    }
    //прописали второй уровень
    for (int i = 0; i < layer1.get_size(); i++) { //для прохода по слою
      error = layer1[res].getX() - layer1[res].getLX();
      weight_delta = consider_weight_delta(error, layer1[i].getX());
      for (int j = 0; j < layer0.get_size(); j++) { //для прохода по весам
        wes1[i][j] = wes1[i][j] - layer0[i].getX() * weight_delta * learning_rate;
      }
    }
    for (int i = 1; i < 4; i++) work_with_l(i);
    //if (q > 3000) break;
  }
}

bool study(string name_of_picture, int result) {
  read_new_img(name_of_picture);
  bool r = 1;
  int era = 0;
  double error, weight_delta;
  for (int i = 1; i < 4; i++) work_with_l(i); //проход вперед сделан
  int res = layer3.nom_max_perceptron();
  if(res!=result) r = 0; //для отчетности- угадал, не угадал
  while ((res != result)&&(era<10)) {
    //cout << "Не равно " << endl;
    for (int i = 1; i < 4; i++) work_with_l(i);
    study_9_zero(result);
    for (int i = 1; i < 4; i++) work_with_l(i);
    study_1_one(result);
    //изменили результаты
    for (int i = 1; i < 4; i++) work_with_l(i);
    res = layer3.nom_max_perceptron();
    era++;
  }
  for (int i = 1; i < 4; i++) work_with_l(i);
  return r;
}




//int new_name_file(int nom_l, int nom_p) {
//  int i1 = 1;
//  while (nom_p / 10 > 0) {
//    i++;
//    nom_p = nom_p / 10;
//  }
//  return  (nom_l * pow(10, i) + nom_p);
//}

int main()
{     
  setlocale(LC_ALL, "Russian");
  int d = 0, f=0;
  int good[10], bad[10], g=0, b=0;
  double db = 0;
  for (int i = 0; i < 10; i++) {
    good[i] = 0;
    bad[i] = 0;
  }
  all_rand_wes();
  int group = 0;
  string add="";
  int k = 1000;
  cout << "Проходит " << k << " картинок." << endl;
  for (int i = 0; i < k; i++) { //2000 
    group = ceach_file_training_group_png(i);
    if (group != -1) {
      add = all_adress_for_training(i, group);
      if (ceach_file_png(add)) {
        if (study(add, group)) {
          good[group]++;
          //cout << "OK" << endl;
        }
        else {
          bad[group]++;
          //cout << "No..." << endl;
        }
      }
    }
    f = i;
    if (((f % 100)==0)&&(f>0)) {
      cout << i << " картинок прошло." << endl;
      b = g; g = 0;
      for (int j = 0; j < 10; j++) {
        g += good[j];
      }
      db = (100-(g-b))/ (g - b);
      cout << "good res- " << (g - b) << ", bad res- " << 100 - (g - b) <<" , отношение- "<< db<< endl;
    }
  }
  for (int i = 0; i < 10; i++) {
    cout << "Good res " << good[i] << " Bad res " << bad[i] << endl;
  }

  system("pause");
  return 0;
}