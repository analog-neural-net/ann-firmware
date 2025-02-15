

class WNBlock:
    def __init__(
        self,
        num_inputs: int,
        neuron_weights: list[list[float]],
        neuron_biases: list[float],
    ):
        self.NUM_OUTPUTS = 4
        self.num_inputs = num_inputs
        if len(neuron_weights) != self.NUM_OUTPUTS:
            raise ValueError(
                f"Expected {self.NUM_OUTPUTS} sets of neuron weights, got "
                f"{len(neuron_weights)}"
            )
        if len(neuron_weights[0]) != self.num_inputs:
            raise ValueError(
                f"Expected {self.num_inputs} weights per neuron, got "
                f"{len(neuron_weights[0])}"
            )
        self.neuron_weights = neuron_weights

    def __str__(self):
        return f"WNBlock(num_inputs={self.num_inputs}, num_outputs={self.NUM_OUTPUTS})"
