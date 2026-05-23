# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    prediction.py                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/30 23:13:59 by jutrera-          #+#    #+#              #
#    Updated: 2024/11/30 23:13:59 by jutrera-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

from . import *

def prediction(theta0, theta1):
	# Entrada del usuario con validación
	while True:
		try:
			mileage = float(input(f"  Enter the mileage: {GREEN}"))
			print(f"{RESET}", end = '')
			if mileage < 0:
				print(f"  {RED}Error: {RESET}Mileage must be a positive number.")
			else:
				break # La entrada es válida
		except ValueError:
			print(f"  {RED}Error: {RESET}Please enter a valid number.")

	# Cálculo de la validación con los valores theta0 y theta1
	price = theta0 + theta1 * mileage
	if (price < 0):
		price = 0
	
	# Salida en el terminal
	print(f"  Predicted price: {GREEN}{price:.2f}{RESET}")
