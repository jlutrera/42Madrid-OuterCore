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

		y_mean = sum(y) / n
		ss_total = sum((yi - y_mean) ** 2 for yi in y)
		ss_residual = sum((yi - y_hat) ** 2 for yi, y_hat in zip(y, y_pred))

		# Coefficient of Determination:
		#   Measures how well the predicted values fit the actual data
		r2 = 100 * (1 - (ss_residual / ss_total))

		print(f"  MAE  = {GREEN}{mae:.2f}{RESET}")
		print(f"  MSE  = {GREEN}{mse:.2f}{RESET}")
		print(f"  RMSE = {GREEN}{rmse:.2f}{RESET}")
		print(f"  R{SQUARE}   = {GREEN}{r2:.2f}{RESET} %")
	else:
		print(f"  {RED}Error: {RESET}The model is untrained.")
