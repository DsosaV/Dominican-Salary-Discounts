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
 * given salary and no more than 2.87% of twenty times the minimum salary (RD$4,965.10).
 *
 * ARS, meaning health insurance discount.
 * In Dominican Republic, as of February 2018, health insurance discount is 3.04% of
 * any given salary and no more than 3.04% of ten times the minimum salary (RD$2,629.60).
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

int main()
{
  // user's monthly salary
  float salary = 0.00f;
  std::cout << "Introduzca su salario mensual: ";
  std::cin >> salary;

  // calculate AFP and ARS discounts as well as the annual salary
  float discountAFP = salary * DISCOUNT_AFP;
  if (discountAFP > DISCOUNT_AFP_MAX) {
      discountAFP = DISCOUNT_AFP_MAX;
  }
  float discountARS = salary * DISCOUNT_ARS;
  if (discountARS > DISCOUNT_ARS_MAX) {
      discountARS = DISCOUNT_ARS_MAX;
  }
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
  std::cout.precision(2);
  std::cout << "Descuento AFP: " << std::fixed << discountAFP << std::endl;
  std::cout << "Descuento ARS: " << std::fixed << discountARS << std::endl;
  std::cout << "Descuento ISR: " << std::fixed << discountISR << std::endl;

  float totalDiscounts = discountAFP + discountARS + discountISR;

  std::cout << "Total Descuentos: " << std::fixed << totalDiscounts << std::endl;
  std::cout << "Sueldo neto: " << std::fixed << salary - totalDiscounts << std::endl;

  return 0;
}
