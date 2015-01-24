function FdT = FDT(F, DT)
% FdT is 4 x 4
FdT = zeros(2*numel(F), 1);

F1 = F(3:8:end);
F2 = F(4:8:end);
F3 = F(7:8:end);
F4 = F(8:8:end);

DT1 = DT(1:4:end);
DT2 = DT(2:4:end);
DT3 = DT(3:4:end);
DT4 = DT(4:4:end);

FdT(1:16:end) = DT1.*F1;
FdT(2:16:end) = DT1.*F2;
FdT(3:16:end) = DT1.*F3;
FdT(4:16:end) = DT1.*F4;
FdT(5:16:end) = DT2.*F1;
FdT(6:16:end) = DT2.*F2;
FdT(7:16:end) = DT2.*F3;
FdT(8:16:end) = DT2.*F4;
FdT(9:16:end) = DT3.*F1;
FdT(10:16:end) = DT3.*F2;
FdT(11:16:end) = DT3.*F3;
FdT(12:16:end) = DT3.*F4;
FdT(13:16:end) = DT4.*F1;
FdT(14:16:end) = DT4.*F2;
FdT(15:16:end) = DT4.*F3;
FdT(16:16:end) = DT4.*F4;
end