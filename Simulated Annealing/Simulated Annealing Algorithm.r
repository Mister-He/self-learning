########################
# Simulated Annealing Algorithm
# Self-written
########################
# Clear the environment
rm(list=ls())
gc()

# Energy function
Energy <- function(x){
  value <- (3-x[1])^2 + (4-x[2])^2
  return(value)
}

# Parameter settings
T0    <- 100        # Initial temperature
T_min <- 0.1        # Lowest temperature
k     <- 0.9        # Annealing rate for temperature (in physics, here should be the Boltzman constant)
count <- 0          # Initial iteration number
maxit <- 100        # Maximum iteration number
x0    <- c(-1,6)    # Initial parameter values
min   <- c(-50,-50) # Lower bound
max   <- c(50,50)   # Upper bound
x     <- c()        # Series of parameters
Obj   <- c()        # Series of objective function values

# Simulated Annealing Algorithm
while (T0>T_min & count <= maxit){
  count <- count + 1 # Update iteration number
  
  E0 <- Energy(x0)  # Current Energy
  x1 <- x0 + 2*c(rbinom(1,1,0.5),rbinom(1,1,0.5))-1 # Random Walk
  x1 <- pmin(pmax(x1, min), max) # Constraints on state space
  E1 <- Energy(x1) # New Energy
  
  # Compare Energy loss
  dE <- E1 - E0
  
  # Metropolis Criteria
  if (dE < 0) {
    x0 <- x1 # Update parameters with prob 1 (absolutely good)
    E0 <- E1
  }
  else if (dE >= 0) {
    prob <- runif(1,0,1) # rejection probabilities
    if (prob <= exp(-dE / T0)){
      x0 <- x1
      E0 <- E1
    }
  }
  
  x <- rbind(x,x0,deparse.level = 0) # Update parameter series
  Obj <- c(Obj,E0) # Update objective function value series
  
  T0 <- k * T0 # Update temperature
  
  cat('Finish iteration',count,'Current Objective value is',tail(Obj,1), ' Current temperature is',T0,'\n')
}

