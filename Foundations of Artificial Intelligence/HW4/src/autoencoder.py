import torch
from tqdm.auto import tqdm
import torch.nn as nn
import torch.optim as optim
import matplotlib.pyplot as plt

# Discuss with b08502041

"""
Implementation of Autoencoder
"""
class Autoencoder(nn.Module):
    def __init__(self, input_dim: int, encoding_dim: int) -> None:
        """
        Modify the model architecture here for comparison
        """
        super(Autoencoder, self).__init__()
        self.encoder = nn.Sequential(
            nn.Linear(input_dim, encoding_dim),
            nn.Linear(encoding_dim, encoding_dim//2),
            nn.ReLU()
        )
        self.decoder = nn.Sequential(
            nn.Linear(encoding_dim//2, encoding_dim),
            nn.Linear(encoding_dim, input_dim),
        )
    
    def forward(self, x):
        #TODO: 5%
        # Hint: a forward pass includes one pass of encoder and decoder
        
        x = self.encoder(x)
        x = self.decoder(x)

        return x
    
    def fit(self, X, epochs=10, batch_size=32):
        #TODO: 5%
        # Hint: a regular pytorch training includes:
        # 1. define optimizer
        # 2. define loss function
        # 3. define number of epochs
        # 4. define batch size
        # 5. define data loader
        # 6. define training loop
        # 7. record loss history 
        # Note that you can use `self(X)` to make forward pass.

        X = torch.Tensor(X)
        criterion = nn.MSELoss()
        optimizer = torch.optim.Adam(self.parameters())
        self.train()

        train_losses = []
        for epoch in range(epochs):
            epoch_loss = 0

            permutation = torch.randperm(X.size()[0])
            for i in range(0, X.size()[0], batch_size):
                indices = permutation[i: (i + batch_size)]
                batch = X[indices, :]
                optimizer.zero_grad()
                outputs = self.forward(batch)

                loss = criterion(outputs, batch)
                loss.backward()
                optimizer.step()

                epoch_loss += loss.item()

            train_losses.append(epoch_loss / len(X))

        self.eval()
    
    def transform(self, X):
        #TODO: 2%
        #Hint: Use the encoder to transofrm X
        
        X = torch.Tensor(X)
        self.eval()

        return self.encoder(X).detach().numpy()
    
    def reconstruct(self, X):
        #TODO: 2%
        #Hint: Use the decoder to reconstruct transformed X
       
        X = torch.Tensor(X)
        self.eval()

        return self.forward(X).detach().numpy()


"""
Implementation of DenoisingAutoencoder
"""
class DenoisingAutoencoder(Autoencoder):
    def __init__(self, input_dim, encoding_dim, noise_factor=0.2):
        super(DenoisingAutoencoder, self).__init__(input_dim,encoding_dim)
        self.noise_factor = noise_factor
    
    def add_noise(self, x):
        #TODO: 3%
        #Hint: Generate Gaussian noise with noise_factor
        
        noise = self.noise_factor * torch.randn(*x.shape)
        return (x + noise)
    
    def fit(self, X, epochs=10, batch_size=32):
        #TODO: 4%
        #Hint: Follow the same procedure above but remember to add_noise before training.
        
        X = torch.Tensor(X)
        criterion = nn.MSELoss()
        optimizer = torch.optim.Adam(self.parameters())
        self.train()
        
        train_losses = []
        for epoch in range(epochs):
            epoch_loss = 0

            permutation = torch.randperm(X.size()[0])
            for i in range(0, X.size()[0], batch_size):
                indices = permutation[i: (i + batch_size)]
                batch = X[indices, :]
                noisy_batch = self.add_noise(batch)
                optimizer.zero_grad()
                outputs = self.forward(noisy_batch)

                loss = criterion(outputs, batch)
                loss.backward()
                optimizer.step()

                epoch_loss += loss.item()

            train_losses.append(epoch_loss / len(X))

        self.eval()
