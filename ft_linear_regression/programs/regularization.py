# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    regularization.py                                  :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/21 20:04:26 by jutrera-          #+#    #+#              #
#    Updated: 2025/03/21 20:04:26 by jutrera-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

from . import *

def elastic_net(x, y):
	# Normalize the data
	x_min, x_max = min(x), max(x)
	norm_x = [(xi - x_min) / (x_max - x_min) for xi in x]
	y_min, y_max = min(y), max(y)
	norm_y = [(yi - y_min) / (y_max - y_min) for yi in y]

	# Initialize parameters
	previous_loss = float('inf')
	theta0, theta1 = 0, 0
	n = len(x)

	# Gradient descent
	for t in range(ITER):
		alpha = ALPHA0 / (1 + K * t)  # Learning rate decay
		# Also could be done with ALPHA0 * (exp(-K * t))
		errors = [theta0 + theta1 * xi - yi for xi, yi in zip(norm_x, norm_y)]

		# Compute gradients with Elastic Net (Ridge + Lasso)
		temp_theta0 = sum(errors) / n
		temp_theta1 = sum(error * xi for error, xi in zip(errors, norm_x)) / n

		# Ridge (L2) penalization
		ridge_penalty = LAMBDA2 * theta1

		# Lasso (L1) penalization
		lasso_penalty = LAMBDA1 * (1 if theta1 > 0 else -1)

		# Update coefficients
		theta0 -= alpha * temp_theta0
		theta1 -= alpha * (temp_theta1 + ridge_penalty + lasso_penalty)

		# Calculate the loss
		loss = sum(error ** 2 for error in errors) / (2 * n)

		# Early stopping
		if previous_loss - loss < EPSILON:
			break
		previous_loss = loss

	# Denormalize the data
	theta1 = theta1 * (y_max - y_min) / (x_max - x_min)
	theta0 = y_min + (theta0 - theta1 * x_min / (x_max - x_min)) * (y_max - y_min)
	print(f"  Model trained with Elastic Net regularization: {LAMBDA}{SUB1}= {LAMBDA1} and  {LAMBDA}{SUB2}= {LAMBDA2}")
	return theta0, theta1

def regularization(x, y):
	if x and y:
		t0, t1 = elastic_net(x,y)
		return t0, t1
	else:
		print(f"  {RED}Error: {RESET}The model is untrained.")
		return 0, 0
