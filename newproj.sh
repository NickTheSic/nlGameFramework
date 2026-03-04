pushd projects
mkdir -p $1
pushd $1

touch $1.c

printf "#include \"nl_lib.h\"


void app_specific_init(void)
{
    
}

void app_specific_update(double dt)
{
    NL_UNUSED(dt);
}

void app_specific_render(void)
{

}

void app_specific_cleanup(void)
{

}" >> $1.c

popd
popd