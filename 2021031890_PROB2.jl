using JuMP
using HiGHS

mutable struct scheduleData
    num_months::Int # número de objetos
    production_cost::Array{Float64} # custo de producao
    demand::Array{Float64} # demanda do cliente
    storage_cost::Array{Float64} # custo de estoque
    penalty::Array{Float64} # peso dos objetos
end

function read_data(file)
    num_months = 0
    production_cost = []
    demand = []
    storage_cost = []
    penalty = []
    for line in eachline(file)
        string = split(line)
        if string[1] == "n"
            num_months = parse(Int64, string[2])
            production_cost = fill(0, num_months)
            demand = fill(0, num_months)
            storage_cost = fill(0, num_months)
            penalty = fill(0, num_months)
        elseif string[1] == "c"
            month = parse(Int64, string[2])
            cost = parse(Float64, string[3])
            production_cost[month] = cost
        elseif string[1] == "d"
            month = parse(Int64, string[2])
            dem = parse(Float64, string[3])
            demand[month] = dem
        elseif string[1] == "s"
            month = parse(Int64, string[2])
            cost = parse(Float64, string[3])
            storage_cost[month] = cost
        elseif string[1] == "p"
            month = parse(Int64, string[2])
            cost = parse(Float64, string[3])
            penalty[month] = cost
        end
    end
    return scheduleData(num_months, production_cost, demand, storage_cost, penalty)
end

model = Model(HiGHS.Optimizer)

file_input = open(ARGS[1], "r")
data = read_data(file_input)
close(file_input)


@variable(model, production[i=1:data.num_months] >= 0 , Int)
@variable(model, storaged[i=1:data.num_months] >= 0, Int)
@variable(model, delivered[i=1:data.num_months] >= 0, Int)
@variable(model, delayed[i=1:data.num_months] >= 0, Int)

@constraint(model, sum(production) == sum(data.demand))
@constraint(model, sum(delivered) == sum(data.demand))

@constraint(model, delayed[1] == 0)
@constraint(model, storaged[data.num_months] == 0) 
# @constraint(model, delivered[data.num_months] == delayed[data.num_months] + production[data.num_months] + storaged[data.num_months-1])

@constraint(model, storaged[1] == production[1] - delivered[1])

for i=2:data.num_months
    @constraint(model, storaged[i] == production[i] + storaged[i-1] - delivered[i])
    @constraint(model, delayed[i] == data.demand[i] - delivered[i] + delayed[i-1])
end

# for i=1:data.num_months
#     @constraint(model, delivered[i] <= data.demand[i] + delayed[i])
# end
                    
@objective(model, Min, (sum(production .* data.production_cost 
                            + storaged .* data.storage_cost
                            + delayed .* data.penalty)))

optimize!(model)

min_cost = Int(objective_value(model))
file_output = open(ARGS[2], "w")

num_months = data.num_months
write(file_output, "$num_months\n")

for i in 1:data.num_months
    write(file_output, join(value(production[i]), " "))
    if i < data.num_months
        write(file_output, "\n")
    end
end

close(file_input)
close(file_output)
