function port_close()
% closes all the serial port object
    if ~isempty(instrfind)
        fclose(instrfind);
        delete(instrfind);
    end
end