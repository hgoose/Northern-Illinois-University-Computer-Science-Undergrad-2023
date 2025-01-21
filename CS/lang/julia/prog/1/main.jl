a = [1,2,3]
println(1 in a) # True
println(5 in a) # False

if 2 in a
    println("2 is in a")
end

# Error: Use occursin
b = "Julia"
println("J" in b)
println("x" in b)
