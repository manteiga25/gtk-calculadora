#include <gtkmm.h>
#include <string>
//#include <iomanip>
//#include <iostream>
//#include <cmath>

using namespace Gtk;
using namespace std;

class Janela : public Window
{
  public:
    Janela();
  private:
    Grid grelha;
    double num1 = -1;
    double num2 = -1;
    double sub_num1 = 0, sub_num2 = 0, res_div = 0, resultado = 0;
    double soma1 = 0, soma2 = 0;
    int contador = 0, contador2 = 0;
 //   unsigned short save = 0;
    string opera = "", saved = "", save = "", save2 = "";
    bool res = false, virgula_num = false, segundo_op = false, continua = false;
    Entry mostrador;
    Button digitos[10];
    Button operacoes[5];
    Button clr;
    Button calcular;
    Button virgula;
    Button del;
    void digitos_click(unsigned short digitos);
    void operacoes_click(unsigned short op);
    void virgula_click();
    void calc();
    void limpar();
    void del_click();
};

int main(int argc, char *argv[])
{
    auto app = Application::create(argc, argv, "org.gtkmm.example");

    Janela janela;

    return app->run(janela);
}

Janela::Janela()
{
  set_size_request(600,600);
  set_position(WIN_POS_CENTER);
  set_resizable(true);
  set_border_width(10);
  set_title("Calculadora");
  grelha.set_row_homogeneous(true);
  grelha.set_column_homogeneous(true);
  grelha.set_row_spacing(5);
  grelha.set_column_spacing(5);
  mostrador.set_editable(true);
  mostrador.set_can_focus(false);
  grelha.attach(mostrador,0,0,5,1);
  for (unsigned short pos = 0; pos < 10; pos++)
  {
    digitos[pos].set_label(to_string(pos));
    digitos[pos].signal_clicked().connect(sigc::bind<unsigned short>(sigc::mem_fun(this, &Janela::digitos_click), pos));
    if (pos >= 1 && pos <= 5)
      grelha.attach(digitos[pos], pos - 1, 1, 1, 1);
    else if (pos >= 6 && pos <= 9)
      grelha.attach(digitos[pos], pos - 6, 2, 1, 1);
    else
      grelha.attach(digitos[pos], 4, 2, 1, 1);
  }
  operacoes[0].set_label("+");
  operacoes[1].set_label("-");
  operacoes[2].set_label("x");
  operacoes[3].set_label("/");
  operacoes[4].set_label("%");
  for (unsigned short pos = 0; pos <= 4; pos++)
  {
    operacoes[pos].signal_clicked().connect(sigc::bind<unsigned short>(sigc::mem_fun(this, &Janela::operacoes_click), pos));
    grelha.attach(operacoes[pos], pos, 3, 1, 1);
  }
  clr.set_label("CLR");
  clr.signal_clicked().connect(sigc::mem_fun(this, &Janela::limpar));
  grelha.attach(clr, 3, 4, 1, 1);
  grelha.set_focus_child(clr);

  calcular.set_label("CALCULAR");
  calcular.signal_clicked().connect(sigc::mem_fun(this, &Janela::calc));
  grelha.attach(calcular, 0, 4, 2, 1);
  
  virgula.set_label(".");
  virgula.signal_clicked().connect(sigc::mem_fun(this, &Janela::virgula_click));
  grelha.attach(virgula, 4, 4, 1, 1);
  
  del.set_label("DELETE");
  del.signal_clicked().connect(sigc::mem_fun(this, &Janela::del_click));
  grelha.attach(del, 2, 4, 1, 1);
  
  add(grelha);
  show_all_children();
  }
  
void Janela::digitos_click(unsigned short digito)
{
 // cout << digito << "\n";
  if (res == 1 && !continua)
  {
    limpar();
  } 
  if (virgula_num) {
    if (segundo_op) {
      ++contador2;
      sub_num2 *= 10;
      sub_num2 += digito;
      save2 += digito;
     // sub_num2 /= pow(10, contador2);
     // sub_num2 /= 10;
      //sub_num2 = (sub_num2 + digito) + pow(10, contador2) / pow(10, contador2);
   //   cout << "contador2 " << contador2 << " sub_num2 " << sub_num2 << "\n";
      }
    else {
      if (!continua) {
      ++contador;
   //   for (int i = 0; i < contador; i++) {
      sub_num1 *= 10;
      sub_num1 += digito;
      save += digito;
   //   sub_num1 /= pow(10, contador);
     // sub_num1 /= 10;
    //  sub_num1 = (sub_num1 + digito) + pow(10, contador) / pow(10, contador); //+ pow(10, contador);
  //    cout << "contador " << contador << " sub_num1 " << sub_num1 << "\n";
      }
      else sub_num1 = resultado;
      
      }
  }
  mostrador.set_text(mostrador.get_text() + to_string(digito));
}

void Janela::del_click() {
if (mostrador.get_text() != "") {
  saved = mostrador.get_text();
//  cout << saved[saved.length() - 1] << endl;
  if (saved.find(".") == string::npos || saved[saved.length() - 1] == '.') { virgula_num = false; }
  if (virgula_num) {
    if (segundo_op && contador2) {
      --contador2;
      sub_num2 -= save2[save2.length() - 1];
      sub_num2 /= 10;
      save2.pop_back();
    //  sub_num2 *= 10;
    //  sub_num2 += digito;
     // sub_num2 /= pow(10, contador2);
     // sub_num2 /= 10;
      //sub_num2 = (sub_num2 + digito) + pow(10, contador2) / pow(10, contador2);
    //  cout << "contador2 " << contador2 << " sub_num2 " << sub_num2 << "\n";
      }
    else if (contador) {
    //  if (!continua) {
      --contador;
      sub_num1 -= save[save.length() - 1];
      sub_num1 /= 10;
      save.pop_back();
   //   for (int i = 0; i < contador; i++) {
   //   sub_num1 *= 10;
   //   sub_num1 += digito;
   //   sub_num1 /= pow(10, contador);
     // sub_num1 /= 10;
    //  sub_num1 = (sub_num1 + digito) + pow(10, contador) / pow(10, contador); //+ pow(10, contador);
   //   cout << "contador " << contador << " sub_num1 " << sub_num1 << "\n";
   //   } 
    //  else sub_num1 = resultado;
      
      }
  }
//  }
  saved.pop_back();
  mostrador.set_text(saved);
}
}

void Janela::virgula_click()
{
    if (!virgula_num)
    {
        mostrador.set_text(mostrador.get_text() + ".");
        virgula_num = true;
    }
}



void Janela::operacoes_click(unsigned short op)
{
if (res == 1) { continua = true; }
  if ((num1 == -1 || continua) && mostrador.get_text() != "") //&& res == 0)
  {
    //if (res == 1) { continua = true; }
    segundo_op = true;
    if (continua)
    num1 = resultado;
    else
    num1 = stol(mostrador.get_text());
    opera = operacoes[op].get_label();
    mostrador.set_text("");
    virgula_num = false;
  }
}

void Janela::calc()
{
  if (num1 != -1 && mostrador.get_text() != "")
  {
  for (int i = contador; i > 0; --i) { sub_num1 /= 10; }
  for (int i = contador2; i > 0; --i) { sub_num2 /= 10; }
    num2 = stol(mostrador.get_text());
 //   cout << num2 << "\n";
    soma1 = (num1 + sub_num1); //* pow(10, contador);
    if (continua && num2 < 1)
    soma2 = sub_num2;
    else
    soma2 = (num2 + sub_num2); //* pow(10, contador2);
//    cout << "soma1 " << soma1 << " soma2 " << soma2 << "\n";
    if (opera == "+") {
    resultado = soma1 + soma2;
      if (((soma1 - (long) soma1 == 0 && soma2 - (long) soma2 == 0) && ( soma2 >= 1 && soma1 >= 1)) || (resultado - (long) resultado == 0)) { // condição para  0r)sultado de numeros inteiro sem mostrar as casas decimais
    //  resultado = (long) soma1 + (long) soma2 + sub_num1 + sub_num2;
      mostrador.set_text(to_string((long) resultado));
      }
      else {
      resultado = soma1 + soma2;
      mostrador.set_text(to_string(resultado));
      }
 //     cout << soma1 << " + " << soma2 << " = " << soma1 + soma2 << endl;
      }
    else if (opera == "-") {
    resultado = soma1 - soma2;
      if (((soma1 - (long) soma1 == 0 && soma2 - (long) soma2 == 0) && ( soma2 >= 1 && soma1 >= 1)) || (resultado - (long) resultado == 0)) {
      resultado = (long) soma1 - (long) soma2;
      mostrador.set_text(to_string((long) resultado));
      }
      else {
      resultado = soma1 - soma2;
      mostrador.set_text(to_string(resultado));
      }
      }
    else if (opera == "x") {
    resultado = soma1 * soma2;
    if (((soma1 - (long) soma1 == 0 && soma2 - (long) soma2 == 0) && ( soma2 >= 1 && soma1 >= 1)) || (resultado - (long) resultado == 0)) {
    //  resultado = (long) soma1 * (long) soma2;
      mostrador.set_text(to_string((long) resultado));
      }
      else {
      resultado = soma1 * soma2;
      mostrador.set_text(to_string(soma1 * soma2));
      }
      }
    else if (opera == "/") {
    if (!soma1 || !soma2)
      mostrador.set_text("Erro, impossível divisão por 0");
    res_div = soma1 / soma2;
    if (res_div - (long) res_div == 0) {
      resultado = (long) soma1 / (long) soma2;
      mostrador.set_text(to_string((long) resultado));
      }
      else {
      resultado = soma1 / soma2;
      mostrador.set_text(to_string(resultado));
      }
      }
      else if (opera == "%") {
    if (!soma1 || !soma2)
      mostrador.set_text("Erro, impossível divisão por 0");
    else if (soma1 - (long) soma1 == 0 || soma2 - (long) soma2 == 0 || (continua && resultado == 0)) {
      res_div = soma1 / soma2;
      if (res_div - (long)res_div == 0) {
        resultado = (long) soma1 % (long) soma2;
        mostrador.set_text(to_string(resultado));
        }
      else 
        mostrador.set_text("Impossível calcular resto de divisão com números flutuantes");
        }
      }
    res = 1;
    virgula_num = false;
    contador2 = 0;
    sub_num1 = sub_num2 = 0;
    num2 = -1;
  }
}

void Janela::limpar()
{
  num1 = -1;
  num2 = -1;
  save2 = save = saved = opera = "";
  res = 0;
 // save = 0;
  continua = virgula_num = segundo_op = false;
  soma1 = soma2 = 0;
  resultado = res_div = sub_num1 = sub_num2 = 0;
  contador = contador2 = 0; 
  mostrador.set_text("");
}
