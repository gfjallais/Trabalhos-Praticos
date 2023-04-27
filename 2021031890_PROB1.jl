using JuMP
using HiGHS

mutable struct binPackingData
    num_objects::Int # número de objetos
    packing_capacity::Int # limite de peso das caixas
    objects::Array{Int64} # peso dos objetos
end

function read_data(file)
    num_objects = 0
    packing_capacity = 0
    objects = []
    for line in eachline(file)
        string = split(line)
        if string[1] == "n"
            num_objects = parse(Int64, string[2])
            objects = fill(0, num_objects)
        elseif string[1] == "l"
            packing_capacity = parse(Int64, string[2])
        elseif string[1] == "o"
            item = parse(Int64, string[2])
            item_weight = parse(Int64, string[3])
            objects[item] = item_weight
        end
    end
    return binPackingData(num_objects, packing_capacity, objects)
end

model = Model(HiGHS.Optimizer)

file_input = open(ARGS[1], "r")
data = read_data(file_input)
close(file_input)


@variable(model, packs[i=1:data.num_objects, j=1:data.num_objects], Bin)
@variable(model, used_packs[i=1:data.num_objects], Bin)


for j=1:data.num_objects
    @constraint(model, sum(data.objects .* packs[:, j]) <= data.packing_capacity * used_packs[j])
    @constraint(model, sum(packs[j,:]) == 1)
    @constraint(model, sum(packs[j,i] for i=1:data.num_objects) <= sum(used_packs))
end

@objective(model, Min, sum(used_packs))

optimize!(model)

num_packs = Int(objective_value(model))
file_output = open(ARGS[2], "w")

write(file_output, "$num_packs\n")


for i=1:data.num_objects
    pack_contents = [j for j in 1:data.num_objects if value(packs[j,i]) > 0]
    if !isempty(pack_contents)
        write(file_output, join(pack_contents, " "))
        if i < data.num_objects
            write(file_output, "\n")
        end
    end
end

close(file_output)
