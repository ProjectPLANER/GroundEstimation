setwd("~/CS Honour Proj. 2020")
library(sp)
options("rgdal_show_exportToProj4_warnings"="none")
library(rgdal)
library(plot3D)

#------FILES--------------------------------------------------------------------
o = cbind("inputs/alaska.tif",
          "./inputs/35422/35422_clipped.tif",
          "./inputs/35322/35322_clipped.tif",
          "./inputs/32377/32377_clipped.tif",
          "./inputs/flat/flat_1.tif",
          "./inputs/flat/flat_2.tif",
          "./inputs/flat/flat_3.tif",
          "./inputs/slight/slight_1.tif",
          "./inputs/slight/slight_2.tif",
          "./inputs/slight/slight_3.tif",
          "./inputs/steep/steep_1.tif",
          "./inputs/steep/steep_2.tif",
          "./inputs/steep/steep_3.tif",
          "./inputs/DanTests/flatOverlap.tif",
          "./inputs/DanTests/flatSpread.tif",
          "./inputs/DanTests/flSmOverlapSimple.tif",
          "./inputs/DanTests/flSmSpreadSimple.tif",
          "./inputs/DanTests/hillsOverlap.tif",
          "./inputs/DanTests/hillSpread.tif",
          "./inputs/DanTests/flatSpreadSimple.tif",
          "./inputs/DanTests/flSmSpread.tif",
          "./inputs/DanTests/hillSmOverlap.tif",
          "./inputs/DanTests/flOverlapSimple.tif")
m = cbind("out/noTreeCircles.tif_masked.tif",#"inputs/noTreeCircles.tif",
          "out/35422_clipped.tif_masked.tif",#"./inputs/35422/35422_treeMaskSlic.tif",
          "out/35322_clipped.tif_masked.tif",#"./inputs/35322/35322_treeMask_SLIC.tif",
          "out/32377_clipped.tif_masked.tif",#"./inputs/32377/32377_treeMask_SLIC.tif",
          "out/flat_1.tif_masked.tif",#"./inputs/flat/flat_1_SlicMask.tif",
          "out/flat_2.tif_masked.tif",#"./inputs/flat/flat_2_SlicMask.tif",
          "out/flat_3.tif_masked.tif",#"./inputs/flat/flat_3_SlicMask.tif",
          "out/slight_1.tif_masked.tif",#"./inputs/slight/slight_1_SlicMask.tif",
          "out/slight_2.tif_masked.tif",#"./inputs/slight/slight_2_SlicMask.tif",
          "out/slight_3.tif_masked.tif",#"./inputs/slight/slight_3_SlicMask.tif",
          "out/steep_1.tif_masked.tif",#"./inputs/steep/steep_1_SlicMask.tif",
          "out/steep_2.tif_masked.tif",#"./inputs/steep/steep_2_SlicMask.tif",
          "out/steep_3.tif_masked.tif",#"./inputs/steep/steep_3_SlicMask.tif",
          "out/flatOverlap.tif_masked.tif",
          "out/flatSpread.tif_masked.tif",
          "out/flSmOverlapSimple.tif_masked.tif",
          "out/flSmSpreadSimple.tif_masked.tif",
          "out/hillsOverlap.tif_masked.tif",
          "out/hillSpread.tif_masked.tif",
          "out/flatSpreadSimple.tif_masked.tif",
          "out/flSmSpread.tif_masked.tif",
          "out/hillSmOverlap.tif_masked.tif",
          "out/flOverlapSimple.tif_masked.tif")
i = cbind("out/noTreeCircles.tif_edited.tif",
          "out/35422_clipped.tif_edited.tif",
          "out/35322_clipped.tif_edited.tif",
          "out/32377_clipped.tif_edited.tif",
          "out/flat_1.tif_edited.tif",
          "out/flat_2.tif_edited.tif",
          "out/flat_3.tif_edited.tif",
          "out/slight_1.tif_edited.tif",
          "out/slight_2.tif_edited.tif",
          "out/slight_3.tif_edited.tif",
          "out/steep_1.tif_edited.tif",
          "out/steep_2.tif_edited.tif",
          "out/steep_3.tif_edited.tif",
          "out/flatOverlap.tif_edited.tif",
          "out/flatSpread.tif_edited.tif",
          "out/flSmOverlapSimple.tif_edited.tif",
          "out/flSmSpreadSimple.tif_edited.tif",
          "out/hillsOverlap.tif_edited.tif",
          "out/hillSpread.tif_edited.tif",
          "out/flatSpreadSimple.tif_edited.tif",
          "out/flSmSpread.tif_edited.tif",
          "out/hillSmOverlap.tif_edited.tif",
          "out/flOverlapSimple.tif_edited.tif")
d = cbind("out/noTreeCircles.tif_difference.tif",
          "out/35422_clipped.tif_difference.tif",
          "out/35322_clipped.tif_difference.tif",
          "out/32377_clipped.tif_difference.tif",
          "out/flat_1.tif_difference.tif",
          "out/flat_2.tif_difference.tif",
          "out/flat_3.tif_difference.tif",
          "out/slight_1.tif_difference.tif",
          "out/slight_2.tif_difference.tif",
          "out/slight_3.tif_difference.tif",
          "out/steep_1.tif_difference.tif",
          "out/steep_2.tif_difference.tif",
          "out/steep_3.tif_difference.tif",
          "out/flatOverlap.tif_difference.tif",
          "out/flatSpread.tif_difference.tif",
          "out/flSmOverlapSimple.tif_difference.tif",
          "out/flSmSpreadSimple.tif_difference.tif",
          "out/hillsOverlap.tif_difference.tif",
          "out/hillSpread.tif_difference.tif",
          "out/flatSpreadSimple.tif_difference.tif",
          "out/flSmSpread.tif_difference.tif",
          "out/hillSmOverlap.tif_difference.tif",
          "out/flOverlapSimple.tif_difference.tif")
c = cbind("out/noTreeCircles.tif_cvp.tif",
          "out/35422_clipped.tif_cvp.tif",
          "out/35322_clipped.tif_cvp.tif",
          "out/32377_clipped.tif_cvp.tif",
          "out/flat_1.tif_cvp.tif",
          "out/flat_2.tif_cvp.tif",
          "out/flat_3.tif_cvp.tif",
          "out/slight_1.tif_cvp.tif",
          "out/slight_2.tif_cvp.tif",
          "out/slight_3.tif_cvp.tif",
          "out/steep_1.tif_cvp.tif",
          "out/steep_2.tif_cvp.tif",
          "out/steep_3.tif_cvp.tif",
          "out/flatOverlap.tif_cvp.tif",
          "out/flatSpread.tif_cvp.tif",
          "out/flSmOverlapSimple.tif_cvp.tif",
          "out/flSmSpreadSimple.tif_cvp.tif",
          "out/hillsOverlap.tif_cvp.tif",
          "out/hillSpread.tif_cvp.tif",
          "out/flatSpreadSimple.tif_cvp.tif",
          "out/flSmSpread.tif_cvp.tif",
          "out/hillSmOverlap.tif_cvp.tif",
          "out/flOverlapSimple.tif_cvp.tif")

#------TESTS--------------------------------------------------------------------
for (j in 2:length(o)){
  origin = readGDAL(o[j], band = 1)
  masked = readGDAL(m[j], band = 1)
  interp = readGDAL(i[j], band = 1)
  
  if(j==1){
    diff = origin
    diff@data = abs(origin@data - interp@data)
  }
  else
  {
    diff = readGDAL(d[j], band = 1)
  }

  print(c("SAME LENGTH"=length(origin@data[,]) == length(interp@data[,])))
  print(c("INTERP<ORIGIN"=length(which(origin@data < interp@data)) == 0))
  print(c("NEGATIVE VALUES"=length(which(diff@data[,] < 0))))
  print(c("EQUAL NAS"=
    length(which(is.na(interp@data[,])))==length(which(is.na(interp@data[,])))))
  
  indices = which(!is.na(diff@data))
  print( c("MEAN"=mean(diff@data[indices,]), "VAR"=var(diff@data[indices,])) )
  
  par(mfrow = c(1,3))
  # image(masked, col = gray.colors(255))
  image(interp, col = gray.colors(255))
  image(origin, col = gray.colors(255))
  image(diff, col = gray.colors(255))
  
  ind = which(masked@data[,]!=origin@data[,])
  table(interp@data[ind,], origin@data[ind,])
  st <- {}
  for (batch in 1:(length(ind)/1000)) {
    subind <- ind[seq(from=batch*1000, length.out=1000)]
    sc.mat <- matrix(c(diff@data[subind,], rep(0,length(subind)*999)), ncol=1000)
    st <- cbind( st, as.matrix(Kappa(sc.mat), ncol=1) )
    print(confint(st[,batch]))
  }
}
#alaska@data[,] = 255
#writeGDAL(alaska, "inputs/alaska_mask.tif")

library(rgl)
j = 2
# t = readGDAL("out/32377_clipped.tif_kriged.tif", band = 1)
z = readGDAL(o[j], band = 1)
t = readGDAL(i[j], band = 1)
v = readGDAL(d[j], band = 1)
w = readGDAL(m[j], band = 1)
z.dims = z@grid@cells.dim
z.dat = as.matrix(z@data,nrow=z.dims[1])
t.dims = t@grid@cells.dim
t.dat = as.matrix(t@data,nrow=t.dims[1])#/1000
v.dims = v@grid@cells.dim
v.dat = as.matrix(v@data,nrow=v.dims[1])#/2
w.dims = w@grid@cells.dim
w.dat = as.matrix(w@data,nrow=w.dims[1])

persp3d(1:z.dims[1], 1:z.dims[2], z.dat, 0.5, col="lightblue", alpha=0.05)
persp3d(1:v.dims[1], 1:v.dims[2], v.dat, 0.5, col="orange", alpha=1, add = TRUE)
persp3d(1:w.dims[1], 1:w.dims[2], w.dat, 0.5, col="darkgreen", alpha=0.5, add = TRUE)
persp3d(1:t.dims[1], 1:t.dims[2], t.dat, 0.5, col="maroon", alpha=1, add = TRUE)

s = readGDAL(c[j], band=1)
s.dims = s@grid@cells.dim
s.dat = as.matrix(s@data[,], nrow=s.dims[1])
persp3d(1:s.dims[1], 1:s.dims[2], s.dat, 0.5, col="red", alpha=1, add=T)
# library(plotly)
# plot_ly(z@data, type="surface")

#----
dem35422 <- c("AvgHeight"=16.04808)


#------errorPlot----
errorScale <- colorRampPalette(c("lightblue", "lightyellow", "pink"))(5)
errorScale[5] <- "red"

plotError <- function(imdat.m, imdat.o, imdat.i_, imdat.dims){
 #imdat is an image of zeroes
  imdat.m@data[imdat.i_,] <- abs(err)
  errs <- imdat.o@data[,]
  errs[which(imdat.m@data[,] <= 0.8)] <- NA
  persp3d(1:imdat.dims[1], 1:imdat.dims[2], as.matrix(errs, nrow=imdat.dims[1]), 
          0.5, col=errorScale[5], alpha=1, add=T)
  errs <- imdat.o@data[,]
  errs[which(imdat.m@data[,] <= 0.4)] <- NA
  persp3d(1:imdat.dims[1], 1:imdat.dims[2], as.matrix(errs, nrow=imdat.dims[1]), 
          0.5, col=errorScale[4], alpha=1, add=T)
  errs <- imdat.o@data[,]
  errs[which(imdat.m@data[,] <= 0.2)] <- NA
  persp3d(1:imdat.dims[1], 1:imdat.dims[2], as.matrix(errs, nrow=imdat.dims[1]), 
          0.5, col=errorScale[3], alpha=1, add=T)
  errs <- imdat.o@data[,]
  errs[which(imdat.m@data[,] <= 0.1)] <- NA
  persp3d(1:imdat.dims[1], 1:imdat.dims[2], as.matrix(errs, nrow=imdat.dims[1]), 
          0.5, col=errorScale[2], alpha=1, add=T)
  errs <- imdat.o@data[,]
  persp3d(1:imdat.dims[1], 1:imdat.dims[2], as.matrix(errs, nrow=imdat.dims[1]), 
          0.5, col=errorScale[1], alpha=1, add=T)
}
#----
Kappa<-function(imdat.m, imdat.o, imdat){
 #assumes a square image
  imdat.i_ <- which(imdat.m@data[,] > 0)
  err <- imdat@data[imdat.i_,] - imdat.o@data[imdat.i_,]
  P0 <- length(which(abs(err) < 1)) / length(err)
  rA.<- range(imdat.o@data[which(!is.na(imdat.o@data[,])),])
  rA <- 1 / (length(imdat.i_)*(rA.[2] - rA.[1]))
  rB <- 1
  gA <- 1 - rA
  gB <- 0
  Pe <- rA*rB + gA*gB
  k  <- (P0 - Pe)/(1 - Pe)
  return (list("kappa"=k, "P0"=P0, "Pe"=Pe))
}

#-----------------------------------------------------contourHillEasy-----------
che <- readGDAL("out/contourHillEasy.tif_edited.tif", band=1)
che.dims <- che@grid@cells.dim
che.dat <- as.matrix(che@data[,], nrow=che.dims[1])
persp3d(1:che.dims[1], 1:che.dims[2], che.dat, 0.5, col="lightblue", alpha=1, add=T)

che.m <- readGDAL("out/DT/contourHillEasy_mask.tif", band=1)
che.i_ <- which(che.m@data[,]!=0)
che.o <- readGDAL("out/DT/contourHillEasy_landscape.tif", band=1)
err <- che@data[che.i_,] - che.o@data[che.i_,]
mean(err*err)
var(err)

plotError(che.m, che.o, che.i_, che.dims)

#-[h]-------------------------------------------------contourHillSmall----------
chs <- readGDAL("out/contourHillSmall.tif_edited.tif", band=1)
chs.dims <- chs@grid@cells.dim
chs.dat <- as.matrix(chs@data[,], nrow=chs.dims[1])
persp3d(1:chs.dims[1], 1:chs.dims[2], chs.dat, 0.5, col="darkgreen", alpha=1, add=T)

chs.m <- readGDAL("out/DT/contourHillSmall_mask.tif", band=1)
chs.i_ <- which(chs.m@data[,]!=0)
chs.o <- readGDAL("out/DT/contourHillSmall_landscape.tif", band=1)
err <- chs@data[chs.i_,] - chs.o@data[chs.i_,]
sqrt(mean(err*err))
var(err)
regss <- sum((chs@data[chs.i_,]-mean(chs@data[chs.i_,]))**2)
tss <- sum((chs.o@data[chs.i_,]-mean(chs.o@data[chs.i_,]))**2)
regss/tss

Kappa(chs.m, chs.o, chs)

#-[h]-------------------------------------------------contourHillSmallSpread----
chss <- readGDAL("out/contourHillSmallSpread.tif_edited.tif", band=1)
chss.dims <- chss@grid@cells.dim
chss.dat <- as.matrix(chss@data[,], nrow=chss.dims[1])
persp3d(1:chss.dims[1], 1:chss.dims[2], chss.dat, 0.5, col="darkgreen", alpha=1, add=T)

chss.m <- readGDAL("out/DT/contourHillSmallSpread_mask.tif", band=1)
chss.i_ <- which(chss.m@data[,]!=0)
chss.o <- readGDAL("out/DT/contourHillSmallSpread_landscape.tif", band=1)
err <- chss@data[chss.i_,] - chss.o@data[chss.i_,]
sqrt(mean(err*err))
var(err)

plotError(chss.m, chss.o, chss.i_, chss.dims)
Kappa(chss.m, chss.o, chss)

regss <- sum((chss@data[chss.i_,]-mean(chss@data[chss.i_,]))**2)
tss <- sum((chss.o@data[chss.i_,]-mean(chss.o@data[chss.i_,]))**2)
regss/tss

#-----------------------------------------------------contourHillSpread---------
chsp <- readGDAL("out/contourHillSpread.tif_edited.tif", band=1)
chsp.dims <- chsp@grid@cells.dim
chsp.dat <- as.matrix(chsp@data[,], nrow=chsp.dims[1])
persp3d(1:chsp.dims[1], 1:chsp.dims[2], chsp.dat, 0.5, col="lightblue", alpha=1, add=T)

chsp.o <- readGDAL("out/DT/contourHillSpread_landscape.tif", band=1)
mean((chsp@data[,] - chsp.o@data[,])**2)
var(chsp@data[,] - chsp.o@data[,])

#-[f]-------------------------------------------------flat----------------------
f <- readGDAL("out/flat.tif_edited.tif", band=1)
f.dims <- f@grid@cells.dim
f.dat <- as.matrix(f@data[,], nrow=f.dims[1])
persp3d(1:f.dims[1], 1:f.dims[2], f.dat, 0.5, col="darkblue", alpha=1, add=T)

f.m <- readGDAL("out/DT/flat_mask.tif", band=1)
f.i_ <- which(f.m@data[,]!=0)
f.o <- readGDAL("out/DT/flat_landscape.tif", band=1)
err <- f@data[f.i_,] - f.o@data[f.i_,]
sqrt(mean(err*err))
var(err)

plotError(f.m, f.o, f.i_, f.dims)
Kappa(f.m, f.o, f)

regss <- sum((f@data[f.i_,]-mean(f@data[f.i_,]))**2)
tss <- sum((f.o@data[f.i_,]-mean(f.o@data[f.i_,]))**2)
regss/tss

#-[f]-------------------------------------------------flatSmall-----------------
fs <- readGDAL("out/flatSmall.tif_edited.tif", band=1)
fs.dims <- fs@grid@cells.dim
fs.dat <- as.matrix(fs@data[,], nrow=fs.dims[1])
persp3d(1:fs.dims[1], 1:fs.dims[2], fs.dat, 0.5, col="darkgreen", alpha=1, add=T)

fs.m <- readGDAL("out/DT/flatSmall_mask.tif", band=1)
fs.i_ <- which(fs.m@data[,]!=0)
fs.o <- readGDAL("out/DT/flatSmall_landscape.tif", band=1)
err <- fs@data[fs.i_,] - fs.o@data[fs.i_,]
sqrt(mean(err*err))
var(err)

Kappa(fs.m, fs.o, fs)

#-----------------------------------------------------flatSmallEasy-------------
fse <- readGDAL("out/flatSmallEasy.tif_edited.tif", band=1)
fse.dims <- fse@grid@cells.dim
fse.dat <- as.matrix(fse@data[,], nrow=fse.dims[1])
persp3d(1:fse.dims[1], 1:fse.dims[2], fse.dat, 0.5, col="lightblue", alpha=1, add=T)

fse.m <- readGDAL("out/DT/flatSmallEasy_mask.tif", band=1)
fse.i_ <- which(fse.m@data[,]!=0)
fse.o <- readGDAL("out/DT/flatSmallEasy_landscape.tif", band=1)
err <- fse@data[fse.i_,] - fse.o@data[fse.i_,]
sqrt(mean(err*err))
var(err)

#-----------------------------------------------------gentleEasy----------------
ge <- readGDAL("out/gentleEasy.tif_edited.tif", band=1)
ge.dims <- ge@grid@cells.dim
ge.dat <- as.matrix(ge@data[,], nrow=ge.dims[1])
persp3d(1:ge.dims[1], 1:ge.dims[2], ge.dat, 0.5, col="darkgreen", alpha=1, add=T)

ge.o <- readGDAL("out/DT/gentleEasy_landscape.tif", band=1)
mean((ge@data[,] - ge.o@data[,])**2)
var(ge@data[,] - ge.o@data[,])

#-_[hl]-----------------------------------------------hills---------------------
h <- readGDAL("out/hills.tif_edited.tif", band=1)
h.dims <- h@grid@cells.dim
h.dat <- as.matrix(h@data[,], nrow=h.dims[1])
persp3d(1:h.dims[1], 1:h.dims[2], 1.5*h.dat, 0.5, col="darkgreen", alpha=1, add=T)

h.m <- readGDAL("out/DT/hills_mask.tif", band=1)
h.i_ <- which(h.m@data[,]!=0)
h.o <- readGDAL("out/DT/hills_landscape.tif", band=1)
err <- h@data[h.i_,] - h.o@data[h.i_,]
mean(err*err)
var(err)

Kappa(h.m, h.o, h)

#-_[hl]-----------------------------------------------hillSpread----------------
hsp <- readGDAL("out/hillSpread.tif_edited.tif", band=1)
hsp.dims <- hsp@grid@cells.dim
hsp.dat <- as.matrix(hsp@data[,], nrow=hsp.dims[1])
persp3d(1:hsp.dims[1], 1:hsp.dims[2], 1.5*hsp.dat, 0.5, col="darkgreen", alpha=1, add=T)

hsp.m <- readGDAL("out/DT/hillSpread_mask.tif", band=1)
hsp.i_ <- which(hsp.m@data[,]!=0)
hsp.o <- readGDAL("out/DT/hillSpread_landscape.tif", band=1)
err <- hsp@data[hsp.i_,] - hsp.o@data[hsp.i_,]
mean(err*err)
var(err)

Kappa(hsp.m, hsp.o, hsp)

#-_---------------------------------------------------hillsEasy-----------------
he <- readGDAL("out/hillsEasy.tif_edited.tif", band=1)
he.dims <- he@grid@cells.dim
he.dat <- as.matrix(he@data[,], nrow=he.dims[1])
persp3d(1:he.dims[1], 1:he.dims[2], he.dat, 0.5, col="lightblue", alpha=1, add=T)

he.o <- readGDAL("out/DT/hillsEasy_landscape.tif", band=1)
mean((he@data[,] - he.o@data[,])**2)
var(he@data[,] - he.o@data[,])

#-_[hl]-----------------------------------------------hillsSmall----------------
hs <- readGDAL("out/hillsSmall.tif_edited.tif", band=1)
hs.dims <- hs@grid@cells.dim
hs.dat <- as.matrix(hs@data[,], nrow=hs.dims[1])
persp3d(1:hs.dims[1], 1:hs.dims[2], 1.5*hs.dat, 0.5, col="darkgreen", alpha=1, add=T)

hs.m <- readGDAL("out/DT/hillsSmall_mask.tif", band=1)
hs.i_ <- which(hs.m@data[,]!=0)
hs.o <- readGDAL("out/DT/hillsSmall_landscape.tif", band=1)
err <- hs@data[hs.i_,] - hs.o@data[hs.i_,]
mean(err*err)
var(err)

plotError(hs.m, hs.o, hs.i_, hs.dims)

#-[s]-------------------------------------------------steep---------------------
st <- readGDAL("out/steep.tif_edited.tif", band=1)
st.dims <- st@grid@cells.dim
st.dat <- as.matrix(st@data[,], nrow=st.dims[1])
persp3d(1:st.dims[1], 1:st.dims[2], st.dat, 0.5, col="darkgreen", alpha=1, add=T)

st.m <- readGDAL("out/DT/steep_mask.tif", band=1)
st.i_ <- which(st.m@data[,]!=0)
st.o <- readGDAL("out/DT/steep_landscape.tif", band=1)
err <- st@data[st.i_,] - st.o@data[st.i_,]
sqrt(mean(err*err))
var(err)

Kappa(st.m, st.o, st)

#-----------------------------------------------------steepSmallEasy------------
sse <- readGDAL("out/steepSmallEasy.tif_edited.tif", band=1)
sse.dims <- sse@grid@cells.dim
sse.dat <- as.matrix(sse@data[,], nrow=sse.dims[1])
persp3d(1:sse.dims[1], 1:sse.dims[2], sse.dat, 0.5, col="lightblue", alpha=1, add=T)

sse.o <- readGDAL("out/DT/steepSmallEasy_landscape.tif", band=1)
mean((sse@data[,] - sse.o@data[,])**2)
var(sse@data[,] - sse.o@data[,])

#-----------------------------------------------------contourHillSmallEasy------
chse <- readGDAL("out/contourHillSmallEasy.tif_edited.tif", band=1)
chse.dims <- chse@grid@cells.dim
chse.dat <- as.matrix(chse@data[,], nrow=chse.dims[1])
persp3d(1:chse.dims[1], 1:chse.dims[2], chse.dat, 0.5, col="lightblue", alpha=1, add=T)

chse.o <- readGDAL("out/DT/contourHillSmallEasy_landscape.tif", band=1)
mean((chse@data[,] - chse.o@data[,])**2)
var(chse@data[,] - chse.o@data[,])

#-[is]------------------------------------------------contourHillJoinSmall------
chjs <- readGDAL("out/contourHillJoinSmall.tif_edited.tif", band=1)
chjs.dims <- chjs@grid@cells.dim
chjs.dat <- as.matrix(chjs@data[,], nrow=chjs.dims[1])
persp3d(1:chjs.dims[1], 1:chjs.dims[2], chjs.dat, 0.5, col="darkgreen", alpha=1, add=T)

chjs.m <- readGDAL("out/DT/contourHillJoinSmall_mask.tif", band=1)
chjs.i_ <- which(chjs.m@data[,]!=0)
chjs.o <- readGDAL("out/DT/contourHillJoinSmall_landscape.tif", band=1)
err <- chjs@data[chjs.i_,] - chjs.o@data[chjs.i_,]
sqrt(mean(err*err))
var(err)

plotError(chjs.m, chjs.o, chjs.i_, chjs.dims)
Kappa(chjs.m, chjs.o, chjs)

#-[s]-------------------------------------------------steepSpread---------------
ss <- readGDAL("out/steepSpread.tif_edited.tif", band=1)
ss.dims <- ss@grid@cells.dim
ss.dat <- as.matrix(ss@data[,], nrow=ss.dims[1])
persp3d(1:ss.dims[1], 1:ss.dims[2], ss.dat, 0.5, col="darkgreen", alpha=1, add=T)

ss.m <- readGDAL("out/DT/steepSpread_mask.tif", band=1)
ss.i_ <- which(ss.m@data[,]!=0)
ss.o <- readGDAL("out/DT/steepSpread_landscape.tif", band=1)
err <- ss@data[ss.i_,] - ss.o@data[ss.i_,]
sqrt(mean(err*err))
var(err)

plotError(ss.m, ss.o, ss.i_, ss.dims)
Kappa(ss.m, ss.o, ss)

#-----------------------------------------------------flatSpread----------------
fsp <- readGDAL("out/flatSpread.tif_edited.tif", band=1)
fsp.dims <- fsp@grid@cells.dim
fsp.dat <- as.matrix(fsp@data[,], nrow=fsp.dims[1])
persp3d(1:fsp.dims[1], 1:fsp.dims[2], fsp.dat, 0.5, col="darkgreen", alpha=1, add=T)

fsp.o <- readGDAL("out/DT/flatSpread_landscape.tif", band=1)
mean((fsp@data[,] - fsp.o@data[,])**2)
var(fsp@data[,] - fsp.o@data[,])

#-_---------------------------------------------------hillsSmallEasy------------
hse <- readGDAL("out/hillsSmallEasy.tif_edited.tif", band=1)
hse.dims <- hse@grid@cells.dim
hse.dat <- as.matrix(hse@data[,], nrow=hse.dims[1])
persp3d(1:hse.dims[1], 1:hse.dims[2], hse.dat, 0.5, col="lightblue", alpha=1, add=T)

hse.o <- readGDAL("out/DT/hillsSmallEasy_landscape.tif", band=1)
mean((hse@data[,] - hse.o@data[,])**2)
var(hse@data[,] - hse.o@data[,])

#-[h]-------------------------------------------------contourHill---------------
ch <- readGDAL("out/contourHill.tif_edited.tif", band=1)
ch.dims <- ch@grid@cells.dim
ch.dat <- as.matrix(ch@data[,], nrow=ch.dims[1])
persp3d(1:ch.dims[1], 1:ch.dims[2], ch.dat, 0.5, col="darkgreen", alpha=1, add=T)

ch.m <- readGDAL("out/DT/contourHill_mask.tif", band=1)
ch.i_ <- which(ch.m@data[,]!=0)
ch.o <- readGDAL("out/DT/contourHill_landscape.tif", band=1)
err <- ch@data[ch.i_,] - ch.o@data[ch.i_,]
sqrt(mean(err*err))
var(err)

#-[s]-------------------------------------------------steepSmall----------------
sts <- readGDAL("out/steepSmall.tif_edited.tif", band=1)
sts.dims <- sts@grid@cells.dim
sts.dat <- as.matrix(sts@data[,], nrow=sts.dims[1])
persp3d(1:sts.dims[1], 1:sts.dims[2], sts.dat, 0.5, col="darkgreen", alpha=1, add=T)

sts.m <- readGDAL("out/DT/steepSmall_mask.tif", band=1)
sts.i_ <- which(sts.m@data[,]!=0)
sts.o <- readGDAL("out/DT/steepSmall_landscape.tif", band=1)
err <- sts@data[sts.i_,] - sts.o@data[sts.i_,]
sqrt(mean(err*err))
var(err)

#-[is]------------------------------------------------contourHillJoin-----------
chj <- readGDAL("out/contourHillJoin.tif_edited.tif", band=1)
chj.dims <- chj@grid@cells.dim
chj.dat <- as.matrix(chj@data[,], nrow=chj.dims[1])
persp3d(1:chj.dims[1], 1:chj.dims[2], chj.dat, 0.5, col="darkgreen", alpha=1, add=T)

chj.m <- readGDAL("out/DT/contourHillJoin_mask.tif", band=1)
chj.i_ <- which(chj.m@data[,]!=0)
chj.o <- readGDAL("out/DT/contourHillJoin_landscape.tif", band=1)
err <- chj@data[chj.i_,] - chj.o@data[chj.i_,]
sqrt(mean(err*err))
var(err)

#-[f]-------------------------------------------------flatSmallSpread-----------
fss <- readGDAL("out/flatSmallSpread.tif_edited.tif", band=1)
fss.dims <- fss@grid@cells.dim
fss.dat <- as.matrix(fss@data[,], nrow=fss.dims[1])
persp3d(1:fss.dims[1], 1:fss.dims[2], fss.dat, 0.5, col="darkgreen", alpha=1, add=T)

fss.m <- readGDAL("out/DT/flatSmallSpread_mask.tif", band=1)
fss.i_ <- which(fss.m@data[,]!=0)
fss.o <- readGDAL("out/DT/flatSmallSpread_landscape.tif", band=1)
err <- fss@data[fss.i_,] - fss.o@data[fss.i_,]
sqrt(mean(err*err))
var(err)

#-X[g]------------------------------------------------gentleSmall---------------
gs <- readGDAL("out/gentleSmall.tif_edited.tif", band=1)
gs.dims <- gs@grid@cells.dim
gs.dat <- as.matrix(gs@data[,], nrow=gs.dims[1])
persp3d(1:gs.dims[1], 1:gs.dims[2], gs.dat, 0.5, col="darkgreen", alpha=1, add=T)

gs.m <- readGDAL("out/DT/gentleSmall_mask.tif", band=1)
gs.i_ <- which(gs.m@data[,]!=0)
gs.o <- readGDAL("out/DT/gentleSmall_landscape.tif", band=1)
err <- gs@data[gs.i_,] - gs.o@data[gs.i_,]
sqrt(mean(err*err))
var(err)

plotError(gs.m, gs.o, gs.i_, gs.dims)
Kappa(gs.m, gs.o, gs)

#-----------------------------------------------------contourHillJoinSmallEasy----
chjse <- readGDAL("out/contourHillJoinSmallEasy.tif_edited.tif", band=1)
chjse.dims <- chjse@grid@cells.dim
chjse.dat <- as.matrix(chjse@data[,], nrow=chjse.dims[1])
persp3d(1:chjse.dims[1], 1:chjse.dims[2], chjse.dat, 0.5, col="lightblue", alpha=1, add=T)

chjse.m <- readGDAL("out/DT/contourHillJoinSmallEasy_mask.tif", band=1)
chjse.i_ <- which(chjse.m@data[,]!=0)
chjse.o <- readGDAL("out/DT/contourHillJoinSmallEasy_landscape.tif", band=1)
err <- chjse@data[chjse.i_,] - chjse.o@data[chjse.i_,]
mean(err*err)
var(err)

plotError(chjse.m, chjse.o, hs.i_, chjse.dims)

#-----------------------------------------------------flatSpreadEasy------------
fspe <- readGDAL("out/flatSpreadEasy.tif_edited.tif", band=1)
fspe.dims <- fspe@grid@cells.dim
fspe.dat <- as.matrix(fspe@data[,], nrow=fspe.dims[1])
persp3d(1:fspe.dims[1], 1:fspe.dims[2], fspe.dat, 0.5, col="lightblue", alpha=1, add=T)

fspe.o <- readGDAL("out/DT/flatSpreadEasy_landscape.tif", band=1)
mean((fspe@data[,] - fspe.o@data[,])**2)
var(fspe@data[,] - fspe.o@data[,])

#-[g]-------------------------------------------------gentleSpread--------------
gsp <- readGDAL("out/gentleSpread.tif_edited.tif", band=1)
gsp.dims <- gsp@grid@cells.dim
gsp.dat <- as.matrix(gsp@data[,], nrow=gsp.dims[1])
persp3d(1:gsp.dims[1], 1:gsp.dims[2], gsp.dat, 0.5, col="darkgreen", alpha=1, add=T)

gsp.m <- readGDAL("out/DT/gentleSpread_mask.tif", band=1)
gsp.i_ <- which(gsp.m@data[,]!=0)
gsp.o <- readGDAL("out/DT/gentleSpread_landscape.tif", band=1)
err <- gsp@data[gsp.i_,] - gsp.o@data[gsp.i_,]
sqrt(mean(err*err))
var(err)

Kappa(gsp.m, gsp.o, gsp)

#-[g]-------------------------------------------------gentle--------------------
g <- readGDAL("out/gentle.tif_edited.tif", band=1)
g.dims <- g@grid@cells.dim
g.dat <- as.matrix(g@data[,], nrow=g.dims[1])
persp3d(1:g.dims[1], 1:g.dims[2], g.dat, 0.5, col="darkgreen", alpha=1, add=T)

g.m <- readGDAL("out/DT/gentle_mask.tif", band=1)
g.i_ <- which(g.m@data[,]!=0)
g.o <- readGDAL("out/DT/gentle_landscape.tif", band=1)
err <- g@data[g.i_,] - g.o@data[g.i_,]
sqrt(mean(err*err))
var(err)

#-----------------------------------------------------contourHillJoinEasy-------
chje <- readGDAL("out/contourHillJoinEasy.tif_edited.tif", band=1)
chje.dims <- chje@grid@cells.dim
chje.dat <- as.matrix(chje@data[,], nrow=chje.dims[1])
persp3d(1:chje.dims[1], 1:chje.dims[2], chje.dat, 0.5, col="lightblue", alpha=1, add=T)

chje.o <- readGDAL("out/DT/contourHillJoinEasy_landscape.tif", band=1)
mean((chje@data[,] - chje.o@data[,])**2)
var(chje@data[,] - chje.o@data[,])

#-----------------------------------------------------flatEasy------------------
fe <- readGDAL("out/flatSpreadEasy.tif_edited.tif", band=1)
fe.dims <- fe@grid@cells.dim
fe.dat <- as.matrix(fe@data[,], nrow=fe.dims[1])
persp3d(1:fe.dims[1], 1:fe.dims[2], fe.dat, 0.5, col="lightblue", alpha=1, add=T)

fe.o <- readGDAL("out/DT/flatSpreadEasy_landscape.tif", band=1)
mean((fe@data[,] - fe.o@data[,])**2)
var(fe@data[,] - fe.o@data[,])

#-----------------------------------------------------steepEasy-----------------
se <- readGDAL("out/steepEasy.tif_edited.tif", band=1)
se.dims <- se@grid@cells.dim
se.dat <- as.matrix(se@data[,], nrow=se.dims[1])
persp3d(1:se.dims[1], 1:se.dims[2], se.dat, 0.5, col="lightblue", alpha=1, add=T)

se.o <- readGDAL("out/DT/steepEasy_landscape.tif", band=1)
mean((se@data[,] - se.o@data[,])**2)
var(se@data[,] - se.o@data[,])

#-_---------------------------------------------------hillsSmooth---------------
hsm <- readGDAL("out/hillsSmooth.tif_edited.tif", band=1)
hsm.dims <- hsm@grid@cells.dim
hsm.dat <- as.matrix(hsm@data[,], nrow=hsm.dims[1])
persp3d(1:hsm.dims[1], 1:hsm.dims[2], hsm.dat, 0.5, col="lightblue", alpha=1, add=T)

hsm.o <- readGDAL("out/DT/hillsSmooth_landscape.tif", band=1)
mean((hsm@data[,] - hsm.o@data[,])**2)
var(hsm@data[,] - hsm.o@data[,])

#-[is]------------------------------------------------contourHillJoinSpread-----
chjsp <- readGDAL("out/contourHillJoinSpread.tif_edited.tif", band=1)
chjsp.dims <- chjsp@grid@cells.dim
chjsp.dat <- as.matrix(chjsp@data[,], nrow=chjsp.dims[1])
persp3d(1:chjsp.dims[1], 1:chjsp.dims[2], chjsp.dat, 0.5, col="darkgreen", alpha=1, add=T)

chjsp.m <- readGDAL("out/DT/contourHillJoinSpread_mask.tif", band=1)
chjsp.i_ <- which(chjsp.m@data[,]!=0)
chjsp.o <- readGDAL("out/DT/contourHillJoinSpread_landscape.tif", band=1)
err <- chjsp@data[chjsp.i_,] - chjsp.o@data[chjsp.i_,]
sqrt(mean(err*err))
var(err)

#-----------------------------------------------------___---------------
stpw__ <- readGDAL("out/contourHillJoinSpread.tif_inp.tif", band=1)
stpw__.dims <- stpw__@grid@cells.dim
stpw__.dat <- as.matrix(stpw__@data[,], nrow=stpw__.dims[1])
persp3d(1:stpw__.dims[1], 1:stpw__.dims[2], stpw__.dat, 0.5, col="darkgreen", alpha=1, add=T)

stpw__.o <- readGDAL("out/DT/contourHillJoinSpread_landscape.tif", band=1)
mean((stpw__@data[,] - stpw__.o@data[,])**2)
var(stpw__@data[,] - stpw__.o@data[,])


trees<-st.m@data[,]-st@data[,]
persp3d(1:hs.o@grid@cells.dim[1], 1:hs.o@grid@cells.dim[2], 
        #as.matrix(1.5*gs.o@data[,], nrow=hs.o@grid@cells.dim[1]), 
        as.matrix(trees, nrow=hs.o@grid@cells.dim[1]),
        0.5, col="darkgreen", alpha=0.5, add=T, aspect = 1:4)
rgl.snapshot("out/R/spur_cvperror.png")
