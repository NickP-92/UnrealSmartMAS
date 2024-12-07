# Multi-Agent System with BDI Agents in Unreal Engine (WIP)

This project showcases the implementation of a Multi-Agent System (MAS) featuring Belief-Desire-Intention (BDI) agents within the Unreal Engine environment. The agents in this system are designed to make intelligent decisions by learning to prioritize and select the most suitable intentions. The learning process is powered by an Artificial Neural Network (ANN), which is trained using Genetic Algorithms (GA) for optimization.

Features

1. BDI Framework Implementation

Beliefs: Represent the agent's perception of the environment.

Desires: Define the agent's high-level goals.

Intentions: Represent the selected actions or plans to achieve the desires based on current beliefs.

Dynamic belief updates and intention reevaluation for realistic behavior.



2. Learning with Artificial Neural Networks (ANN)

Agents utilize an ANN to evaluate the potential outcomes of various intentions.

The network predicts the success or utility of specific actions based on historical data.



3. Optimization via Genetic Algorithms (GA)

The ANN training process leverages a GA to evolve the network's weights.

The GA ensures efficient learning by applying selection, crossover, and mutation to find optimal solutions.



4. Integration with Unreal Engine

Designed for seamless simulation and visualization in Unreal Engine.

Supports multi-agent interactions in complex 3D environments.



5. Extensibility and Customization

Modular and extensible codebase allows for customization of agent behaviors, ANN structures, and GA parameters.

Easily adaptable for other MAS projects or AI research.
