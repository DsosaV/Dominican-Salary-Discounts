/*
 * This program calculates all discounts that apply to a given monthly salary
 * in Dominican Republic as of February 2018.
 *
 * Minimum public salary in Dominican Republic as of February 2018 is RD$9,411.60
 * which is around US$194.25 (current exchange rate is: US$1.00 = RD$48.45)
 *
 * Discounts are:
 *
 * AFP, meaning pension fund discount
 * In Dominican Republic, as of February 2018, pension discount is 2.87% of any
 * given salary.
 *
 * ARS, meaning health insurance discount.
 * In Dominican Republic, as of February 2018, health insurance discount is 3.04% of
 * any given salary.
 *
 * ISR, meaning income tax.
 * Income tax in the Dominican Republic, for individual people, is calculated
 * using the following criteria:
 *
 *      if the annual salary is no more than 416,220.00 dominican pesos, then NO
 *      income tax is taken from the person's salary.
 *
 *      if the annual salary is more than 416,220.00 but no more than 624,329.00
 *      dominican pesos, then annual income tax is 15% excess of 416,220.00
 *
 *      if the annual salary is more than 624,329.00 but no more than 867,123.00
 *      dominican pesos, then annual income tax is 31,216.00 + 20% excess
 *      of 624,329.00
 *
 *      if the annual salary is more than 867,123.00 dominican pesos, then annual
 *      income tax is 79,776.00 + 25% excess of 867,123.00
 *
 * Income tax calculation is based on the criteria published by the government on its website
 * http://dgii.gob.do/informacionTributaria/principalesImpuestos/Paginas/Impuesto-Sobre-la-Renta.aspx
 *
 * 2015/06/11 10:24 AM Santo Domingo, Dominican Republic
 * UPDATED:
 * Added AFP max and ARS max values.
 * 2015/11/30 10:54 AM Santo Domingo, Dominican Republic
 * UPDATED:
 * Updated all values.
 * 2018/02/23 02:02 PM Santo Domingo, Dominican Republic
 * UPDATED:
 * Removed AFP max and ARS max values.
 * 2018/03/28 01:35 PM Santo Domingo, Dominican Republic
 * @author: David Sosa
 */
#include <iostream>

const float MINIMUM_SALARY = 9411.60f;
const float DISCOUNT_AFP = 0.0287f;
const float DISCOUNT_ARS = 0.0304f;
const float DISCOUNT_AFP_MAX = MINIMUM_SALARY * 20 * DISCOUNT_AFP;
const float DISCOUNT_ARS_MAX = MINIMUM_SALARY * 10 * DISCOUNT_ARS;

const float ISR1 = 867123.00f;
const float ISR2 = 624329.00f;
const float ISR3 = 416220.00f;

const float EXCEED1 = 79776.00f;
const float EXCEED2 = 31216.00f;

int main(int argc, const char* agrv[])
{
  using namespace std;
  // user's monthly salary
  float salary = 0.00f;
  if (argc > 1) {
    salary = atof(agrv[1]);
  } else {
    cout << "Introduzca su salario mensual: ";
    cin >> salary;
    cout << endl;
  }

  // calculate AFP and ARS discounts as well as the annual salary
  float discountAFP = salary * DISCOUNT_AFP;
  float discountARS = salary * DISCOUNT_ARS;
  float annualSalary = (salary - discountAFP - discountARS) * 12;

  // calcualte income tax
  float discountISR = 0.00f;
  if (annualSalary > ISR1) {
      discountISR = (EXCEED1 + (annualSalary - ISR1) * 0.25f) / 12;
  } else if (annualSalary > ISR2) {
      discountISR = (EXCEED2 + (annualSalary - ISR2) * 0.20f) / 12;
  } else if (annualSalary > ISR3) {
      discountISR = ((annualSalary - ISR3) * 0.15f) / 12;
  }

  // print results
  cout.precision(2);
  cout << "Descuento AFP: " << fixed << discountAFP << endl;
  cout << "Descuento ARS: " << fixed << discountARS << endl;
  cout << "Descuento ISR: " << fixed << discountISR << endl;

  float totalDiscounts = discountAFP + discountARS + discountISR;

  cout << "Total Descuentos: " << fixed << totalDiscounts << endl;
  cout << "Sueldo neto: " << fixed << salary - totalDiscounts << endl;

  return 0;
}
