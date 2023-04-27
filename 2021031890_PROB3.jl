using JuMP, HiGHS

mutable struct graphData
    num_nodes::Int # número de vertices
    edges::Array{Tuple{Int64, Int64, Int64}, 1}
end

function read_data(file)
    num_nodes = 0
    edges = []
    for line in eachline(file)
        string = split(line)
        if string[1] == "n"
            num_nodes = parse(Int64, string[2])
        elseif string[1] == "e"
            i = parse(Int64, string[2])
            j = parse(Int64, string[3])
            weight = parse(Int64, string[4])
            push!(edges, (i, j, weight))
        end
    end
    return graphData(num_nodes, edges)
end

function findNewCycles(path)
    global graph
    global cycles
    start_node = path[1]
    next_node = nothing
    sub = []

    #visit each edge and each node of each edge
    for edge in graph
        node1, node2 = edge
        if start_node in edge
            if node1 == start_node
                next_node = node2
            else
                next_node = node1
            end
            if !visited(next_node, path)
                # neighbor node not on path yet
                sub = [next_node]
                append!(sub, path)
                # explore extended path
                findNewCycles(sub)
            elseif length(path) > 2 && next_node == path[end]
                # cycle found
                p = rotate_to_smallest(path)
                inv = invert(p)
                if isNew(p) && isNew(inv)
                    push!(cycles, p)
                end
            end
        end
    end
end

# invert cycle path
function invert(path)
    return rotate_to_smallest(reverse(path))
end

# rotate cycle path such that it begins with the smallest node
function rotate_to_smallest(path)
    n = findfirst(path .== minimum(path))
    return vcat(path[n:end], path[1:n-1])
end

function isNew(path)
    return !(path in cycles)
end

function visited(node, path)
    return node in path
end

function extractEdges(cycle)
    edges = []
    push!(edges, (cycle[1], cycle[length(cycle)]))
    for i=1:length(cycle)-1
        push!(edges, (cycle[i], cycle[i+1]))
    end
    return edges
end


model1 = Model(HiGHS.Optimizer)

file_input = open(ARGS[1], "r")
data = read_data(file_input)
close(file_input)


@variable(model1, maxSpanningTree[i=1:length(data.edges)], Bin)

@constraint(model1, sum(maxSpanningTree) == data.num_nodes-1)

for i=1:data.num_nodes
    @constraint(model1, sum(maxSpanningTree[j] for j=1:length(data.edges) if data.edges[j][1] == i || data.edges[j][2] == i) >= 1)
end

@objective(model1, Max, sum(maxSpanningTree[i]*data.edges[i][3] for i=1:length(data.edges)))
# Solve the model1
optimize!(model1)


global graph
global cycles
global binaryListOfCycles
binaryListOfCycles = []
cycles = []

function reoptimize()
    global graph = [[data.edges[i][1], data.edges[i][2]] for i=1:length(data.edges) if value(maxSpanningTree[i]) == 1]

    for edge in graph
        for node in edge
            findNewCycles([node])
        end
    end

    prevNumOfCycles = length(binaryListOfCycles)
    for cycle in cycles
        cycleVector = zeros(length(data.edges))
        cycleEdges = extractEdges(cycle)
        for edge in cycleEdges
            for j=1:length(data.edges)
                if (data.edges[j][1] == edge[1] && data.edges[j][2] == edge[2]) || (data.edges[j][1] == edge[2] && data.edges[j][2] == edge[1])
                    cycleVector[j] = 1
                end
            end
        end
        if !(cycleVector in binaryListOfCycles)
            push!(binaryListOfCycles, cycleVector)
        end
    end

    

    if prevNumOfCycles != length(binaryListOfCycles)
        for cycle in binaryListOfCycles
            @constraint(model1, sum(maxSpanningTree .* cycle) <= sum(cycle)-1)
        end
        optimize!(model1)
        reoptimize()
    end
end

reoptimize()

max_sum = Int(objective_value(model1))
num_nodes = data.num_nodes
file_output = open(ARGS[2], "w")

write(file_output, "$num_nodes\n")
# write(file_output, "$max_sum\n")


for i=1:length(data.edges)
    if value(maxSpanningTree[i]) > 0
        u, v, w = data.edges[i]
        write(file_output, "$u $v\n")
    end
end

close(file_output)