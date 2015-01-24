function dH = DH(X, DX, p)
% parameters
b = p(2);
d1 = p(3);
d2 = p(4);
k1 = p(6);
k2 = p(7);

% state
x4 = X(4:8:end);
x7 = X(7:8:end);
x8 = X(8:8:end);

s4 = sin(x4);
c4 = cos(x4);
cd4 = cos(2*x4);

% DX is 4 x 4
sdx = size(DX);
DX = reshape(DX, numel(DX), 1);

% dH is 4 x 4
dH = zeros(2*numel(X), 1);

div = d1^2 - 2*k1*k2 + d1^2*cd4;

% dHdX is 4 x 4
dH(1:16:end) = 1;
% dH(2:16:end) = 0;
% dH(3:16:end) = 0;
% dH(4:16:end) = 0;
dH(5:16:end) = 1;
dH(6:16:end) = -1;
dH(7:16:end) = (-2*d1*s4.*((-4*c4*d2*k1*(b*d1 - k2) ...
    + (d1 - b*k1)*(d1^2 + cd4*d1^2 + 2*k1*k2)).*x7 ...
    + 4*c4*d2*k1.*(-(b*d1) + k2).*x8))./div.^2;
dH(8:16:end) = (2*s4.*(((d1^2 - b*d1*(d2 + k1) + d2*k2)*(d1^2 ...
    + cd4*d1^2 + 2*k1*k2) + 4*c4*d1.*((d1^2 + d2*k1)*k2 ...
    - b*d1*k1*(d2 + k2))).*x7 - d2*(b*d1 - k2)*(d1^2 + cd4*d1^2 ...
    + 4*c4*d1*k1 + 2*k1*k2).*x8))./div.^2;
% dH(9:16:end) = 0;
% dH(10:16:end) = 0;
dH(11:16:end) = (d1^2 + cd4*d1*(d1 - d2) - d1*d2 + 2*b*d2*k1 ...
    - 2*c4*d1*(d1 - b*k1) - 2*k1*k2)./div;
dH(12:16:end) = (cd4*d1*(-(b*d1) + d2) - b*(d1^2 + 2*d2*k1) ...
    + d1*(d2 + 2*k2) + 2*c4*(d1^2 - b*d1*(d2 + k1) + d2*k2))./div;
% dH(13:16:end) = 0;
% dH(14:16:end) = 0;
dH(15:16:end) = (d1 - d2 + (2*d2*k1*(b*d1 - k2))./div)/d1;
dH(16:16:end) = (-d1^2 + d1*d2 + cd4*d1*(-d1 + d2) - 2*b*d2*k1 ...
    + 2*k1*k2 + 2*c4*d2*(-(b*d1) + k2))./div;
% dHdxsi is 4 x 4
dH = reshape(DHDX(dH, DX), sdx);
end

function dH = DHDX(DH, DX)
% dHdxsi is 4 x 4
dH = zeros(numel(DX), 1);

% DX
DX1 = DX(1:16:end);
DX2 = DX(2:16:end);
DX3 = DX(3:16:end);
DX4 = DX(4:16:end);
DX5 = DX(5:16:end);
DX6 = DX(6:16:end);
DX7 = DX(7:16:end);
DX8 = DX(8:16:end);
DX9 = DX(9:16:end);
DX10 = DX(10:16:end);
DX11 = DX(11:16:end);
DX12 = DX(12:16:end);
DX13 = DX(13:16:end);
DX14 = DX(14:16:end);
DX15 = DX(15:16:end);
DX16 = DX(16:16:end);

% DH
DH1 = DH(1:16:end);
DH2 = DH(2:16:end);
DH3 = DH(3:16:end);
DH4 = DH(4:16:end);
DH5 = DH(5:16:end);
DH6 = DH(6:16:end);
DH7 = DH(7:16:end);
DH8 = DH(8:16:end);
DH9 = DH(9:16:end);
DH10 = DH(10:16:end);
DH11 = DH(11:16:end);
DH12 = DH(12:16:end);
DH13 = DH(13:16:end);
DH14 = DH(14:16:end);
DH15 = DH(15:16:end);
DH16 = DH(16:16:end);

% DH*DX
dH(1:16:end) = DH1.*DX1 + DH5.*DX2 + DH9.*DX3 + DH13.*DX4;
dH(2:16:end) = DH2.*DX1 + DH6.*DX2 + DH10.*DX3 + DH14.*DX4;
dH(3:16:end) = DH3.*DX1 + DH7.*DX2 + DH11.*DX3 + DH15.*DX4;
dH(4:16:end) = DH4.*DX1 + DH8.*DX2 + DH12.*DX3 + DH16.*DX4;
dH(5:16:end) = DH1.*DX5 + DH5.*DX6 + DH9.*DX7 + DH13.*DX8;
dH(6:16:end) = DH2.*DX5 + DH6.*DX6 + DH10.*DX7 + DH14.*DX8;
dH(7:16:end) = DH3.*DX5 + DH7.*DX6 + DH11.*DX7 + DH15.*DX8;
dH(8:16:end) = DH4.*DX5 + DH8.*DX6 + DH12.*DX7 + DH16.*DX8;
dH(9:16:end) = DH1.*DX9 + DH5.*DX10 + DH9.*DX11 + DH13.*DX12;
dH(10:16:end) = DH2.*DX9 + DH6.*DX10 + DH10.*DX11 + DH14.*DX12;
dH(11:16:end) = DH3.*DX9 + DH7.*DX10 + DH11.*DX11 + DH15.*DX12;
dH(12:16:end) = DH4.*DX9 + DH8.*DX10 + DH12.*DX11 + DH16.*DX12;
dH(13:16:end) = DH1.*DX13 + DH5.*DX14 + DH9.*DX15 + DH13.*DX16;
dH(14:16:end) = DH2.*DX13 + DH6.*DX14 + DH10.*DX15 + DH14.*DX16;
dH(15:16:end) = DH3.*DX13 + DH7.*DX14 + DH11.*DX15 + DH15.*DX16;
dH(16:16:end) = DH4.*DX13 + DH8.*DX14 + DH12.*DX15 + DH16.*DX16;
end