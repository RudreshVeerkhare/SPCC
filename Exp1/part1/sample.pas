program learn;

uses
    crt;

(* This is a Commment 1*)

{ This is a Commment 2 }

// This is a Commment 3

var
    a, b, c, e, f, right: integer;
    d: real;
label
1, 2, 3, 4, 5;
begin
    textbackground(green);
    textcolor(white);
    clrscr;
    repeat
        Inc(f);
    until f = 100000;
    randomize;
    1:
        e := random(3) + 1;
    b := random(200) + 1;
    c := random(200) + 1;
    if e = 1 then
        d := b + c;
    if e = 2 then
        d := b - c;
    if e = 3 then
        d := b * c;
    writeln('    ', b: 3);
    if e = 1 then
        write('+ ');
    if e = 2 then
        write('- ');
    if e = 3 then
        write('x ');
    writeln(c: 3);
    writeln('______');
    readln(a);
    if a = d then
    begin
        Inc(right);
        writeln('HORRAY! YOU GOT IT RIGHT! you have ', right, ' points!');
    end
    else
    begin
        right := right - 1;
        writeln('WRONG! you have ', right, ' points');
    end;
    goto 1;
end