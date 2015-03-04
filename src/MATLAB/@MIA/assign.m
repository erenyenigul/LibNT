function obj = assign(obj,otherMIA,assign_order)
%assigns from otherMIA to obj, based on the index_order, e.g., [2 1 3]
%means that otherMIA is assigned to obj as obj(ijk)=otherMIA(jik)
if (isa(otherMIA,'SparseMIA'))
    obj=SparseMIA;
    obj=obj.assign(otherMIA,assign_order);
elseif(isa(otherMIA,'MIA') )
    if otherMIA.order>1
        obj.data=permute(otherMIA.data,assign_order);
    else
        obj.data=otherMIA.data;
    end
    
else %TODO as SparseMIA (above MIA)
    error('Incompatible object used in assignment');
end

end

