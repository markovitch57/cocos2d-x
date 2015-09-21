
--------------------------------
-- @module GLProgramCache
-- @extend Ref
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#GLProgramCache] addCustomShader 
-- @param self
-- @param #char pcVertexShaderText
-- @param #char pcFragmentShaderText
-- @param #unsigned int dShaderFlags
-- @param #char key
-- @return GLProgramCache#GLProgramCache self (return value: cc.GLProgramCache)
        
--------------------------------
-- 
-- @function [parent=#GLProgramCache] reloadCustomShaders 
-- @param self
-- @return GLProgramCache#GLProgramCache self (return value: cc.GLProgramCache)
        
--------------------------------
--  adds a GLProgram to the cache for a given name 
-- @function [parent=#GLProgramCache] addGLProgram 
-- @param self
-- @param #cc.GLProgram program
-- @param #string key
-- @return GLProgramCache#GLProgramCache self (return value: cc.GLProgramCache)
        
--------------------------------
--  reload default programs these are relative to light 
-- @function [parent=#GLProgramCache] reloadDefaultGLProgramsRelativeToLights 
-- @param self
-- @return GLProgramCache#GLProgramCache self (return value: cc.GLProgramCache)
        
--------------------------------
--  reload the default shaders 
-- @function [parent=#GLProgramCache] reloadDefaultGLPrograms 
-- @param self
-- @return GLProgramCache#GLProgramCache self (return value: cc.GLProgramCache)
        
--------------------------------
-- 
-- @function [parent=#GLProgramCache] bindAttributesToShader 
-- @param self
-- @param #cc.GLProgram shaderProgram
-- @param #unsigned int dShaderFlags
-- @return GLProgramCache#GLProgramCache self (return value: cc.GLProgramCache)
        
--------------------------------
--  loads the default shaders 
-- @function [parent=#GLProgramCache] loadDefaultGLPrograms 
-- @param self
-- @return GLProgramCache#GLProgramCache self (return value: cc.GLProgramCache)
        
--------------------------------
--  returns a GL program for a given key 
-- @function [parent=#GLProgramCache] getGLProgram 
-- @param self
-- @param #string key
-- @return GLProgram#GLProgram ret (return value: cc.GLProgram)
        
--------------------------------
--  purges the cache. It releases the retained instance. 
-- @function [parent=#GLProgramCache] destroyInstance 
-- @param self
-- @return GLProgramCache#GLProgramCache self (return value: cc.GLProgramCache)
        
--------------------------------
--  returns the shared instance 
-- @function [parent=#GLProgramCache] getInstance 
-- @param self
-- @return GLProgramCache#GLProgramCache ret (return value: cc.GLProgramCache)
        
--------------------------------
-- Constructor.<br>
-- js ctor
-- @function [parent=#GLProgramCache] GLProgramCache 
-- @param self
-- @return GLProgramCache#GLProgramCache self (return value: cc.GLProgramCache)
        
return nil
