# Code the bisection method

function bisect(f, a, b; maxiters=1000, tol=0.0)
    fa, fb = f(a), f(b)
    for i in 1:maxiters
        p = (a+b)/2
        fp = f(p)

        if (fa * fp < 0)
            a, fa = p, fp
        elseif (fa * fp > 0)
            b, fb = p, fp
        else 
            break
        end
    end
    return p
end
f(x) = 2cosh(x/4) - x
a, b = 5.0, 10.0

j = bisect(f, a, b, tol=0.0)
println(j, f(j))
