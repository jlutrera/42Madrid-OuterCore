# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    errors.py                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/30 23:12:36 by jutrera-          #+#    #+#              #
#    Updated: 2024/11/30 23:12:36 by jutrera-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import statistics
import matplotlib.pyplot as plt

from . import *


def errors(x, y, theta0, theta1):
	if x and y and theta0 is not None and theta1 is not None:
		n = len(x)
		y_pred = [theta0 + theta1 * xi for xi in x]
		errors = [yi - y_hat for yi, y_hat in zip(y, y_pred)]

		# Mean Absolute Error:
		#   Measures the average of the absolute differences between
		#   the actual values and the predicted values
		mae = sum(abs(error) for error in errors) / n
		# Mean Squared Error:
		#   Computes the average of the squared errors
		mse = sum(error ** 2 for error in errors) / n
		# Root Mean Squared Error:
		#   It is simply the square root of the MSE
		rmse = mse ** 0.5

		# Coefficient of Determination:
		#   Measures how well the predicted values fit the actual data
		y_mean = sum(y) / n
		ss_total = sum((yi - y_mean) ** 2 for yi in y)
		if ss_total == 0:
			ss_total = EPS  # Avoid division by zero
		ss_residual = sum((yi - y_hat) ** 2 for yi, y_hat in zip(y, y_pred))	
		r2 = 100 * (1 - (ss_residual / ss_total))

		print(f"{CYAN}----------------------------------------{RESET}")
		print(f"{CYAN}             ERRORS ANALYSIS            {RESET}")
		print(f"{CYAN}----------------------------------------{RESET}\n")
		print(f"  MAE  = {GREEN}{mae:.2f}{RESET}")
		print(f"  MSE  = {GREEN}{mse:.2f}{RESET}")
		print(f"  RMSE = {GREEN}{rmse:.2f}{RESET}")
		print(f"  R{SQUARE}   = {GREEN}{r2:.2f}{RESET} %")

		return errors
	else:
		print(f"  {RED}Error: {RESET}The model is untrained.")


def detect_outliers(x, y, theta0, theta1, factor=2.0):
    """
    Detecta outliers basándose en los errores residuales del modelo lineal.
    factor = número de desviaciones estándar por encima del cual se marca un outlier.
    """

    # Obtenemos los errores individuales usando tu función
    residuals = errors(x, y, theta0, theta1)
    abs_res = [abs(r) for r in residuals]

    # Estadísticas básicas
    mean_res = statistics.mean(abs_res)
    std_res = statistics.stdev(abs_res) if len(abs_res) > 1 else 0

    # Umbral para marcar outliers
    threshold = mean_res + factor * std_res

    # Índices de los puntos que superan el umbral
    outliers_idx = [i for i, r in enumerate(abs_res) if r > threshold]

    # Empaquetamos información útil
    outliers = [
        {
            "index": i,
            "x": x[i],
            "y": y[i],
            "pred": theta0 + theta1 * x[i],
            "residual": residuals[i],
            "abs_residual": abs_res[i]
        }
        for i in outliers_idx
    ]

    return {
        "threshold": threshold,
        "mean_abs_error": mean_res,
        "std_abs_error": std_res,
        "outliers": outliers
    }


def print_outliers_report(x, y, theta0, theta1, factor=2.0):
    if x and y and theta0 is not None and theta1 is not None:
        result = detect_outliers(x, y, theta0, theta1, factor=factor)

        print(f"{CYAN}----------------------------------------{RESET}")
        print(f"{CYAN} OUTLIER ANALYSIS (factor = {factor}){RESET}")
        print(f"{CYAN}----------------------------------------{RESET}\n")

        print(f"  Threshold        : {YELLOW}{result['threshold']:.2f}{RESET}")
        print(f"  Mean |residual|  : {YELLOW}{result['mean_abs_error']:.2f}{RESET}")
        print(f"  Std  |residual|  : {YELLOW}{result['std_abs_error']:.2f}{RESET}\n")

        outliers = result["outliers"]

        if not outliers:
            print(f"  {GREEN}No outliers detected.{RESET}")
            return

        print(f"{MAGENTA}  Outliers found:{RESET}\n")

        #   Cálculo de anchos
        id_w    = max(len("idx"),   max(len(str(o["index"])) for o in outliers))
        x_w     = max(len("x"),     max(len(f"{o['x']:.2f}") for o in outliers))
        y_w     = max(len("y"),     max(len(f"{o['y']:.2f}") for o in outliers))
        pred_w  = max(len("pred"),  max(len(f"{o['pred']:.2f}") for o in outliers))
        resid_w = max(len("resid"), max(len(f"{o['residual']:.2f}") for o in outliers))

        # Encabezado alineado
        header = (
            f"  {BONW}"
            f"{'idx':>{id_w}}  "
            f"{'x':>{x_w}}  "
            f"{'y':>{y_w}}  "
            f"{'pred':>{pred_w}}  "
            f"{'resid':>{resid_w}}"
            f"{RESET}"
        )
        print(header)

        # Filas alineadas
        for o in outliers:
            id_val    = f"{o['index']:>{id_w}}"
            x_val     = f"{o['x']:.2f}".rjust(x_w)
            y_val     = f"{o['y']:.2f}".rjust(y_w)
            pred_val  = f"{o['pred']:.2f}".rjust(pred_w)
            resid_val = f"{o['residual']:.2f}".rjust(resid_w)

            print(f"  {RED}{id_val}  {x_val}  {y_val}  {pred_val}  {resid_val}{RESET}")

        print()
    else:
        print(f"  {RED}Error: {RESET}The model is untrained.")
