# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    training.py                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/30 23:14:08 by jutrera-          #+#    #+#              #
#    Updated: 2024/11/30 23:14:08 by jutrera-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

from . import *
import csv

# --- LECTURA DE DATOS DEL ARCHIVO CSV ---
def read_csv_data():
	mileage = []
	price = []
	csv_file = input("Enter the name of the CSV (with the relative path): ")

	try:
		with open(csv_file, 'r') as file:
			reader = csv.reader(file)
			next(reader)
			for row in reader:
				mileage.append(float(row[0]))
				price.append(float(row[1]))
	except Exception as e:
		print(f"  {RED}Error: {RESET}{e.args[1]}")
		return None, None

	return mileage, price

# --- CÁLCULO DE LOS VALORES REQUERIDOS ---
def calc_values(x, y):
	# Normalización Min-Max
	x_min, x_max = min(x), max(x)
	y_min, y_max = min(y), max(y)

	norm_x = [(xi - x_min) / (x_max - x_min + EPS) for xi in x]
	norm_y = [(yi - y_min) / (y_max - y_min + EPS) for yi in y]

	# Inicialización
	previous_loss = float('inf')
	theta0, theta1 = 0, 0
	n = len(x)
	alphas = []

	# Gradient Descent
	for t in range(ITER):
		# Learning rate decay
		alpha = ALPHA0 / (1 + K * t) # También podría ser: ALPHA0 * (exp(-K * t))
		alphas.append(alpha)

		errors = [theta0 + theta1 * xi - yi for xi, yi in zip(norm_x, norm_y)]

		# Gradientes
		grad0 = sum(errors) / n
		grad1 = sum(error * xi for error, xi in zip(errors, norm_x)) / n

		# Actualización simultánea
		theta0 -= alpha * grad0
		theta1 -= alpha * grad1

		# Cálculo del coste
		loss = sum(e * e for e in errors) / (2 * n)
		
		# Early stopping
		if previous_loss - loss < EPSILON:
			break

		previous_loss = loss

	# Desnormalización
	b = theta1 * (y_max - y_min) / (x_max - x_min)
	a = y_min + theta0 * (y_max - y_min) - b * x_min

	return a, b, alphas, t

# --- PROGRAMA PRINCIPAL ---
def training():
	# Lectura de datos del archivo
	mileage, price = read_csv_data()

	# Cálculo de los parámetros requeridos
	if mileage and price:
		theta0, theta1, alphas, t = calc_values(mileage, price)
		return mileage, price, theta0, theta1, alphas, t

	# Si no hay datos válidos, devolvemos lo que ya había
	return mileage, price, None, None, [], 0
