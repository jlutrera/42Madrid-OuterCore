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
	while True:
		try:
			mileage = float(input(f"  Enter the mileage: {GREEN}"))
			print(f"{RESET}", end = '')
			if mileage < 0:
				print(f"  {RED}Error: {RESET}Mileage must be a positive number.")
			else:
				break
		except ValueError:
			print(f"  {RED}Error: {RESET}Please enter a valid number.")

	price = theta0 + theta1 * mileage
	if (price < 0):
		price = 0
	
	print(f"  Predicted price: {GREEN}{price:.2f}{RESET}")
