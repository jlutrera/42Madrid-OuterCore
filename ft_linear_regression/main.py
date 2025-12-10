# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    main.py                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/30 23:13:16 by jutrera-          #+#    #+#              #
#    Updated: 2024/11/30 23:13:16 by jutrera-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

from programs import *
from programs.prediction import prediction
from programs.training import training
from programs.plottings import plot_data, plot_alpha
from programs.coefficients import coefficients
from programs.errors import errors
from programs.regularization import regularization
import os, sys


def wait_for_keypress():
	message = f"\n{BONW}Press a key to continue...{RESET}"
	if os.name == 'nt':  # Windows
		import msvcrt
		print(message, end = '', flush = True)
		msvcrt.getch()
	else:  # Linux
		print(message, end = '', flush = True)
		import termios
		import tty
		fd = sys.stdin.fileno()
		old_settings = termios.tcgetattr(fd)
		try:
			tty.setraw(fd)
			sys.stdin.read(1)
		finally:
			termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)

def clear_terminal():
	# Linux
	if os.name == 'posix':
		os.system('clear')
	# Windows
	elif os.name == 'nt':
		os.system('cls')

def print_menu(theta0, theta1):
	clear_terminal()
	print(f"{CYAN}************************************{RESET}")
	print(f"{CYAN}***     FT_LINEAR_REGRESSION     ***{RESET}")
	print(f"{CYAN}************************************{RESET}\n")
	if theta0 == 0 and theta1 == 0:
		print(f"Current model: {RED}UNTRAINED{RESET}\n")
	else:
		print(f"Current model: {GREEN}TRAINED{RESET}\n")
	print(f"{CYAN}MANDATORY:{RESET}")
	print(f"  {YELLOW}1{RESET}. Predict the price of a car with a given mileage")
	print(f"  {YELLOW}2{RESET}. Train the model with a CSV file.\n")
	print(f"{CYAN}BONUS:{RESET}")
	print(f"  {YELLOW}3{RESET}. Plot the data and the regression line")
	print(f"  {YELLOW}4{RESET}. Print the equation and coefficients")
	print(f"  {YELLOW}5{RESET}. Print the prediction errors")
	print(f"  {YELLOW}6{RESET}. Plot the learning rate")
	print(f"  {YELLOW}7{RESET}. Apply regularization\n")
	print(f"  {YELLOW}r{RESET}. Reset")
	print(f"  {YELLOW}q{RESET}. Quit\n")
	
	option = input(f"Type an option (1-7, r, q): {YELLOW}")
	print(f"{RESET}\n", end = '')
	
	return option

def main():
	theta0, theta1, mileage, price, alphas, t = 0, 0, [], [], [], 0
	while True:
		option = print_menu(theta0, theta1)
		e = 0
		match option:
			case '1':
				prediction(theta0, theta1)
			case '2':
				mileage, price, theta0, theta1, alphas, t, e = training()
			case '3':
				e = plot_data(mileage, price, theta0, theta1)
			case '4':
				coefficients(mileage, price, theta0, theta1)
			case '5':
				errors(mileage, price, theta0, theta1)
			case '6':
				e = plot_alpha(alphas, t)
			case '7':
				theta0, theta1 = regularization(mileage, price)
			case 'r':
				theta0, theta1, mileage, price, alphas, t = 0, 0, [], [], [], 0
			case 'q':
				break
			case _:
				print(f"  {RED}Error: {RESET}Please, enter a valid option.")
		if  e == 0:
			wait_for_keypress()
	
	print(f"{CYAN}BYE!{RESET}\n")

if __name__ == "__main__":
	main()