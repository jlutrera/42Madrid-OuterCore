#__init__.py

# Colours
RESET	= "\033[0m"
BONW	= "\033[30;47m"
RED		= "\033[31m"
GREEN	= "\033[32m"
YELLOW	= "\033[33m"
BLUE	= "\033[34m"
MAGENTA	= "\033[35m"
CYAN	= "\033[36m"

# Symbols
THETA	= "\u03B8"
ALPHA	= '\u03B1'
SQUARE	= '\u00B2'
SUB0	= '\u2080'
SUB1	= '\u2081'
SUB2	= '\u2082'
DOT		= '\u00B7'
LAMBDA	= '\u03BB'

# Constants
K		= 0.0001 	# Decay rate
ALPHA0	= 0.1  		# Initial learning rate
EPSILON	= 1e-8 		# Stop when the loss is not decreasing significantly
ITER	= 1000000 	# Maximum number of iterations
LAMBDA1	= 0.3		# Lasso: Performs feature selection
LAMBDA2	= 0.1 		# Ridge: Reduces overfitting

# For imports
__all__ = [
	"RESET", "BONW", "RED", "GREEN", "YELLOW", "BLUE", "MAGENTA", "CYAN", 
	"THETA", "ALPHA", "SQUARE", "SUB0", "SUB1", "SUB2", "DOT", "LAMBDA",
	"K", "ALPHA0", "EPSILON", "ITER", "LAMBDA1", "LAMBDA2"
	]