# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    plotting.py                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/30 23:13:41 by jutrera-          #+#    #+#              #
#    Updated: 2024/11/30 23:13:41 by jutrera-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

from . import *
import matplotlib.pyplot as plt

def plot_alpha(alphas, iterations):
	if alphas is not None and iterations > 0:
		# Clear the plot
		if plt.fignum_exists(1):
			plt.close(1)
		plt.ion()
		plt.figure(1)
		manager = plt.get_current_fig_manager()
		manager.set_window_title('ft_linear_regression')
		# Plot the learning rate decay
		plt.plot(alphas, color='blue')
		plt.xlabel('Iterations')
		plt.ylabel('Learning Rate')
		plt.title(f'Learning Rate Decay : {ALPHA} = {ALPHA}{SUB0} / (1 + k{DOT}t)')
		plt.grid(True)

		# manager = plt.get_current_fig_manager()
		# if hasattr(manager, "toolbar"):
		# 	manager.toolbar.setVisible(False)
		plt.get_current_fig_manager().canvas.manager.toolbar.pack_forget()

		plt.text(0.7, 0.9, f'{ALPHA} = [{alphas[0]:.2f}, {alphas[-1]:.2f}]', transform=plt.gca().transAxes, ha='left', fontsize=12)
		plt.text(0.7, 0.85, f't  = [0, {iterations}]', transform=plt.gca().transAxes, ha='left', fontsize=12)
		plt.text(0.7, 0.8, f'k = {K}', transform=plt.gca().transAxes, ha='left', fontsize=12)

		plt.show()
		plt.draw()
		plt.pause(0.1)
		return 1
	else:
		print(f"  {RED}Error: {RESET}The model is untrained.")
		return 0


def plot_data(mileage, price, theta0, theta1):
	if mileage and price and theta0 is not None and theta1 is not None:
		# Clear the plot
		if plt.fignum_exists(2):
			plt.close(2)
		plt.ion()
		plt.figure(2)
		manager = plt.get_current_fig_manager()
		manager.set_window_title('ft_linear_regression')
		# Original data points
		plt.scatter(mileage, price, color='blue', label='Original Data')
		# Generate points for the regression line
		x_min = min(mileage)
		x_max = max(mileage)
		x_line = [x_min, x_max]
		y_line = [theta0 + theta1 * x_min, theta0 + theta1 * x_max]
		# Plot the line
		if theta1 < 0:
			plt.plot(x_line, y_line, color='red', label=f'Regression Line: y = {theta0:.2f} - {-theta1:.2f}{DOT}x')
		else:
			plt.plot(x_line, y_line, color='red', label=f'Regression Line: y = {theta0:.2f} + {theta1:.2f}{DOT}x')
		# Configure the plot
		plt.xlabel('Mileage')
		plt.ylabel('Price')
		plt.title('Linear Regression line & data')
		plt.legend()
		plt.grid(True)
		
		# manager = plt.get_current_fig_manager()
		# if hasattr(manager, "toolbar"):
		# 	manager.toolbar.setVisible(False)
		plt.get_current_fig_manager().canvas.manager.toolbar.pack_forget()

		plt.show()
		plt.draw()
		plt.pause(0.1)
		return 1
	else:
		print(f"  {RED}Error: {RESET}The model is untrained.")
		return 0
