x.mat <- read.table(file = "x_mat.csv",sep = ",", header=T)

dimnames(x.mat)[[1]] <- x.mat[,1]
x.mat <- x.mat[,-1]
x.mat2 <- x.mat[,c(1:6,(ncol(x.mat)-29):(ncol(x.mat)))]
comp.case <- complete.cases(x.mat2)
x.mat2 <- x.mat2[comp.case,]
x.mat2 <- data.matrix(x.mat2)

y.mat <- read.table(file = "y_vect.csv",sep = ",", header=T)

dimnames(y.mat)[[1]] <- y.mat[,1]
y.mat <- y.mat[,-1]
y.mat <- y.mat[comp.case]
y.mat <- data.matrix(y.mat)

ptm <- proc.time()
################### 
res <- t(x.mat2) %*% x.mat2
res1 <- solve(res)
res2 <- res1 %*% t(x.mat2)
beta <- res2 %*% as.numeric(y.mat)
#######################
proc.time()-ptm

res3 <- res %*% res1

write.table(x.mat2,"x_file.txt",row.names = F,col.names=F)
write.table(t(x.mat2), "xt_file.txt", row.names=F, col.names=F)
write.table(res,"xtx_file.txt",row.names = F,col.names=F)
write.table(res1,"xtx1_file.txt",row.names = F,col.names=F)
write.table(res2,"xtx1xt_file.txt",row.names = F,col.names=F)
write.table(y.mat,"y_file.txt",row.names = F,col.names=F)
write.table(beta,"beta_file.txt",row.names = F,col.names=F)



