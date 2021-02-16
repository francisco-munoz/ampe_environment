import torch
import torch_stonne

i = torch.LongTensor([[0, 1, 1],[2, 0, 2]])
v = torch.FloatTensor([3, 4, 5])
sm=torch.sparse.FloatTensor(i, v, torch.Size([2,3]))
dm=torch.randn(3,3)
output = torch_stonne.simulated_sparsedense_matmul("SparseDenseGEMM", sm, dm, 1, 3, "../../simulation_files/magma_128mses_128_bw.cfg")
print(output)
print(torch.sparse.mm(sm, dm))
