function dslns = DX(slns, DX0, U, DU, p, options)
dslns = ode45(@dzdt, slns.x([1 end]), DX0, options);
    function dZ = dzdt(t, Z)
        X = deval(slns, t);
        [DxF, DuF] = DF(t, X, U, p);
        dZ = Fx(DxF, Z) + Fu(DuF, DU(t, X));
    end
end

function dFu = Fu(DuF, V)
% dFu is 4 x 4
dFu = zeros(2*numel(V), 1);

v1 = V(1:8:end);
v2 = V(2:8:end);
v3 = V(3:8:end);
v4 = V(4:8:end);
v5 = V(5:8:end);
v6 = V(6:8:end);
v7 = V(7:8:end);
v8 = V(8:8:end);

DuF1 = DuF(1:8:end);
DuF2 = DuF(2:8:end);
DuF3 = DuF(3:8:end);
DuF4 = DuF(4:8:end);
DuF5 = DuF(5:8:end);
DuF6 = DuF(6:8:end);
DuF7 = DuF(7:8:end);
DuF8 = DuF(8:8:end);

dFu(1:16:end) = DuF1.*v1 + DuF5.*v2;
dFu(2:16:end) = DuF2.*v1 + DuF6.*v2;
dFu(3:16:end) = DuF3.*v1 + DuF7.*v2;
dFu(4:16:end) = DuF4.*v1 + DuF8.*v2;
dFu(5:16:end) = DuF1.*v3 + DuF5.*v4;
dFu(6:16:end) = DuF2.*v3 + DuF6.*v4;
dFu(7:16:end) = DuF3.*v3 + DuF7.*v4;
dFu(8:16:end) = DuF4.*v3 + DuF8.*v4;
dFu(9:16:end) = DuF1.*v5 + DuF5.*v6;
dFu(10:16:end) = DuF2.*v5 + DuF6.*v6;
dFu(11:16:end) = DuF3.*v5 + DuF7.*v6;
dFu(12:16:end) = DuF4.*v5 + DuF8.*v6;
dFu(13:16:end) = DuF1.*v7 + DuF5.*v8;
dFu(14:16:end) = DuF2.*v7 + DuF6.*v8;
dFu(15:16:end) = DuF3.*v7 + DuF7.*v8;
dFu(16:16:end) = DuF4.*v7 + DuF8.*v8;
end

function dFx = Fx(DxF, Z)
% dFxsi is 4 x 4
dFx = zeros(numel(Z), 1);

% state DPhi
z1 = Z(1:16:end);
z2 = Z(2:16:end);
z3 = Z(3:16:end);
z4 = Z(4:16:end);
z5 = Z(5:16:end);
z6 = Z(6:16:end);
z7 = Z(7:16:end);
z8 = Z(8:16:end);
z9 = Z(9:16:end);
z10 = Z(10:16:end);
z11 = Z(11:16:end);
z12 = Z(12:16:end);
z13 = Z(13:16:end);
z14 = Z(14:16:end);
z15 = Z(15:16:end);
z16 = Z(16:16:end);

DxF1 = DxF(1:16:end);
DxF2 = DxF(2:16:end);
DxF3 = DxF(3:16:end);
DxF4 = DxF(4:16:end);
DxF5 = DxF(5:16:end);
DxF6 = DxF(6:16:end);
DxF7 = DxF(7:16:end);
DxF8 = DxF(8:16:end);
DxF9 = DxF(9:16:end);
DxF10 = DxF(10:16:end);
DxF11 = DxF(11:16:end);
DxF12 = DxF(12:16:end);
DxF13 = DxF(13:16:end);
DxF14 = DxF(14:16:end);
DxF15 = DxF(15:16:end);
DxF16 = DxF(16:16:end);

dFx(1:16:end) = DxF1.*z1 + DxF5.*z2 + DxF9.*z3 + DxF13.*z4;
dFx(2:16:end) = DxF2.*z1 + DxF6.*z2 + DxF10.*z3 + DxF14.*z4;
dFx(3:16:end) = DxF3.*z1 + DxF7.*z2 + DxF11.*z3 + DxF15.*z4;
dFx(4:16:end) = DxF4.*z1 + DxF8.*z2 + DxF12.*z3 + DxF16.*z4;
dFx(5:16:end) = DxF1.*z5 + DxF5.*z6 + DxF9.*z7 + DxF13.*z8;
dFx(6:16:end) = DxF2.*z5 + DxF6.*z6 + DxF10.*z7 + DxF14.*z8;
dFx(7:16:end) = DxF3.*z5 + DxF7.*z6 + DxF11.*z7 + DxF15.*z8;
dFx(8:16:end) = DxF4.*z5 + DxF8.*z6 + DxF12.*z7 + DxF16.*z8;
dFx(9:16:end) = DxF1.*z9 + DxF5.*z10 + DxF9.*z11 + DxF13.*z12;
dFx(10:16:end) = DxF2.*z9 + DxF6.*z10 + DxF10.*z11 + DxF14.*z12;
dFx(11:16:end) = DxF3.*z9 + DxF7.*z10 + DxF11.*z11 + DxF15.*z12;
dFx(12:16:end) = DxF4.*z9 + DxF8.*z10 + DxF12.*z11 + DxF16.*z12;
dFx(13:16:end) = DxF1.*z13 + DxF5.*z14 + DxF9.*z15 + DxF13.*z16;
dFx(14:16:end) = DxF2.*z13 + DxF6.*z14 + DxF10.*z15 + DxF14.*z16;
dFx(15:16:end) = DxF3.*z13 + DxF7.*z14 + DxF11.*z15 + DxF15.*z16;
dFx(16:16:end) = DxF4.*z13 + DxF8.*z14 + DxF12.*z15 + DxF16.*z16;
end